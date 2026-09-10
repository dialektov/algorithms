#!/usr/bin/env python3
"""Generate and execute the seminar experiment notebook."""

from __future__ import annotations

import json
import time
import traceback
from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
import openml
import pandas as pd
import seaborn as sns
from IPython.display import DisplayObject
from lightgbm import LGBMClassifier
from sklearn.compose import ColumnTransformer
from sklearn.impute import SimpleImputer
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, get_scorer
from sklearn.model_selection import GridSearchCV, StratifiedKFold, cross_val_score
from sklearn.neural_network import MLPClassifier
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.ensemble import RandomForestClassifier
from xgboost import XGBClassifier

SEED = 42
OUT_DIR = Path("/workspace/nis_doklad")
FIG_DIR = OUT_DIR / "figures"
FIG_DIR.mkdir(parents=True, exist_ok=True)

# OpenML task/dataset IDs commonly used in tabular papers.
# We load by dataset id for simplicity.
DATASETS = [
    {"name": "blood-transfusion", "openml_id": 1464, "note": "мало признаков, относительно простой"},
    {"name": "diabetes", "openml_id": 37, "note": "медицинский, умеренный размер"},
    {"name": "credit-g", "openml_id": 31, "note": "много категориальных, irregular-ish"},
    {"name": "pc4", "openml_id": 1049, "note": "software defect, дисбаланс"},
    {"name": "madelon", "openml_id": 1485, "note": "много шумовых признаков"},
]


def skew_irregularity(X: pd.DataFrame) -> float:
    """Simple irregularity proxy: mean abs skewness of numeric columns."""
    num = X.select_dtypes(include=[np.number])
    if num.shape[1] == 0:
        return 0.0
    skews = num.skew(numeric_only=True).abs().replace([np.inf, -np.inf], np.nan).dropna()
    if len(skews) == 0:
        return 0.0
    return float(skews.mean())


def make_preprocessor(X: pd.DataFrame) -> ColumnTransformer:
    num_cols = X.select_dtypes(include=[np.number]).columns.tolist()
    cat_cols = [c for c in X.columns if c not in num_cols]
    transformers = []
    if num_cols:
        transformers.append(
            (
                "num",
                Pipeline(
                    [
                        ("imputer", SimpleImputer(strategy="median")),
                        ("scaler", StandardScaler()),
                    ]
                ),
                num_cols,
            )
        )
    if cat_cols:
        transformers.append(
            (
                "cat",
                Pipeline(
                    [
                        ("imputer", SimpleImputer(strategy="most_frequent")),
                        (
                            "onehot",
                            OneHotEncoder(handle_unknown="ignore", sparse_output=False),
                        ),
                    ]
                ),
                cat_cols,
            )
        )
    return ColumnTransformer(transformers)


def load_dataset(openml_id: int):
    ds = openml.datasets.get_dataset(openml_id, download_data=True)
    X, y, _, _ = ds.get_data(target=ds.default_target_attribute, dataset_format="dataframe")
    # Drop constant / all-null columns
    X = X.dropna(axis=1, how="all")
    nunique = X.nunique(dropna=False)
    X = X.loc[:, nunique > 1]
    # Encode target to 0..K-1
    y = pd.Series(y).astype("category").cat.codes
    return X, y, ds.name


def build_models(n_classes: int):
    xgb = XGBClassifier(
        n_estimators=200,
        max_depth=4,
        learning_rate=0.1,
        subsample=0.9,
        colsample_bytree=0.9,
        objective="binary:logistic" if n_classes == 2 else "multi:softprob",
        eval_metric="logloss",
        random_state=SEED,
        n_jobs=2,
        tree_method="hist",
    )
    lgbm = LGBMClassifier(
        n_estimators=200,
        max_depth=-1,
        learning_rate=0.1,
        subsample=0.9,
        colsample_bytree=0.9,
        random_state=SEED,
        n_jobs=2,
        verbose=-1,
    )
    models = {
        "LogReg": LogisticRegression(max_iter=2000, random_state=SEED),
        "RF": RandomForestClassifier(n_estimators=200, random_state=SEED, n_jobs=2),
        "MLP": MLPClassifier(
            hidden_layer_sizes=(128, 64),
            max_iter=200,
            early_stopping=True,
            random_state=SEED,
        ),
        "XGBoost": xgb,
        "LightGBM": lgbm,
    }
    return models


def choose_scoring(y: pd.Series) -> str:
    if y.nunique() == 2:
        return "roc_auc"
    return "accuracy"


def eval_model(name, model, pre, X, y, scoring):
    pipe = Pipeline([("pre", pre), ("model", model)])
    cv = StratifiedKFold(n_splits=5, shuffle=True, random_state=SEED)
    t0 = time.time()
    scores = cross_val_score(pipe, X, y, cv=cv, scoring=scoring, n_jobs=1)
    elapsed = time.time() - t0
    return {
        "model": name,
        "mean": float(scores.mean()),
        "std": float(scores.std()),
        "seconds": elapsed,
        "scores": scores.tolist(),
    }


def tune_xgb(pre, X, y, scoring, n_classes: int):
    base = XGBClassifier(
        objective="binary:logistic" if n_classes == 2 else "multi:softprob",
        eval_metric="logloss",
        random_state=SEED,
        n_jobs=2,
        tree_method="hist",
    )
    pipe = Pipeline([("pre", pre), ("model", base)])
    param_grid = {
        "model__n_estimators": [100, 300],
        "model__max_depth": [3, 6],
        "model__learning_rate": [0.05, 0.1],
    }
    cv = StratifiedKFold(n_splits=3, shuffle=True, random_state=SEED)
    grid = GridSearchCV(pipe, param_grid, cv=cv, scoring=scoring, n_jobs=1)
    t0 = time.time()
    grid.fit(X, y)
    elapsed = time.time() - t0
    # Refit best with 5-fold for comparable score
    best = grid.best_estimator_
    cv5 = StratifiedKFold(n_splits=5, shuffle=True, random_state=SEED)
    scores = cross_val_score(best, X, y, cv=cv5, scoring=scoring, n_jobs=1)
    return {
        "best_params": grid.best_params_,
        "mean": float(scores.mean()),
        "std": float(scores.std()),
        "seconds": elapsed,
    }


def main():
    rows = []
    meta_rows = []
    tune_rows = []
    errors = []

    print("Loading datasets and evaluating models...")
    for spec in DATASETS:
        try:
            X, y, real_name = load_dataset(spec["openml_id"])
            irregularity = skew_irregularity(X)
            scoring = choose_scoring(y)
            meta_rows.append(
                {
                    "dataset": spec["name"],
                    "openml_name": real_name,
                    "n": len(X),
                    "d": X.shape[1],
                    "n_classes": int(y.nunique()),
                    "irregularity_skew": irregularity,
                    "scoring": scoring,
                    "note": spec["note"],
                }
            )
            print(f"\n=== {spec['name']} ({real_name}) n={len(X)} d={X.shape[1]} skew={irregularity:.3f} ===")
            pre = make_preprocessor(X)
            for mname, model in build_models(int(y.nunique())).items():
                res = eval_model(mname, model, pre, X, y, scoring)
                res["dataset"] = spec["name"]
                res["scoring"] = scoring
                res["irregularity_skew"] = irregularity
                rows.append(res)
                print(f"  {mname:10s} {scoring}={res['mean']:.4f}±{res['std']:.4f} ({res['seconds']:.1f}s)")

            # Light tuning on XGBoost vs default gap to best NN-like (MLP)
            tuned = tune_xgb(pre, X, y, scoring, int(y.nunique()))
            default_xgb = next(r for r in rows if r["dataset"] == spec["name"] and r["model"] == "XGBoost")
            mlp = next(r for r in rows if r["dataset"] == spec["name"] and r["model"] == "MLP")
            family_gap = abs(default_xgb["mean"] - mlp["mean"])
            tune_gain = tuned["mean"] - default_xgb["mean"]
            tune_rows.append(
                {
                    "dataset": spec["name"],
                    "xgb_default": default_xgb["mean"],
                    "xgb_tuned": tuned["mean"],
                    "mlp": mlp["mean"],
                    "tune_gain": tune_gain,
                    "family_gap_xgb_mlp": family_gap,
                    "tune_ge_family_gap": bool(tune_gain >= family_gap - 1e-12),
                    "best_params": str(tuned["best_params"]),
                }
            )
            print(
                f"  TUNING: gain={tune_gain:.4f}, |XGB-MLP|={family_gap:.4f}, "
                f"tune>=gap={tune_gain >= family_gap - 1e-12}"
            )
        except Exception as e:
            errors.append({"dataset": spec["name"], "error": str(e), "trace": traceback.format_exc()})
            print(f"ERROR on {spec['name']}: {e}")

    results = pd.DataFrame(rows)
    meta = pd.DataFrame(meta_rows)
    tune = pd.DataFrame(tune_rows)

    results.to_csv(OUT_DIR / "results.csv", index=False)
    meta.to_csv(OUT_DIR / "datasets_meta.csv", index=False)
    tune.to_csv(OUT_DIR / "tuning_comparison.csv", index=False)

    # Pivot for plot
    if not results.empty:
        pivot = results.pivot(index="dataset", columns="model", values="mean")
        order = meta.sort_values("irregularity_skew")["dataset"].tolist()
        pivot = pivot.reindex(order)

        fig, ax = plt.subplots(figsize=(10, 5))
        pivot.plot(kind="bar", ax=ax)
        ax.set_title("Качество моделей vs датасеты (упорядочены по irregularity/skew)")
        ax.set_ylabel("CV score (ROC-AUC или accuracy)")
        ax.legend(loc="best", fontsize=8)
        ax.set_xticklabels(ax.get_xticklabels(), rotation=25, ha="right")
        fig.tight_layout()
        fig.savefig(FIG_DIR / "model_scores.png", dpi=150)
        plt.close(fig)

        # GBDT avg vs MLP
        results["family"] = results["model"].map(
            {
                "XGBoost": "GBDT",
                "LightGBM": "GBDT",
                "MLP": "NN",
                "RF": "baseline",
                "LogReg": "baseline",
            }
        )
        fam = (
            results[results["family"].isin(["GBDT", "NN"])]
            .groupby(["dataset", "family"])["mean"]
            .mean()
            .unstack()
        )
        fam = fam.reindex(order)
        fam["GBDT - NN"] = fam["GBDT"] - fam["NN"]
        fig, ax = plt.subplots(figsize=(8, 4))
        colors = ["#34d399" if v >= 0 else "#f87171" for v in fam["GBDT - NN"]]
        fam["GBDT - NN"].plot(kind="bar", ax=ax, color=colors)
        ax.axhline(0, color="#94a3b8", lw=1)
        ax.set_title("Преимущество GBDT над MLP (положительное = GBDT лучше)")
        ax.set_ylabel("Δ score")
        ax.set_xticklabels(ax.get_xticklabels(), rotation=25, ha="right")
        fig.tight_layout()
        fig.savefig(FIG_DIR / "gbdt_minus_mlp.png", dpi=150)
        plt.close(fig)

        if not tune.empty:
            fig, ax = plt.subplots(figsize=(8, 4))
            x = np.arange(len(tune))
            ax.bar(x - 0.15, tune["tune_gain"], width=0.3, label="Прирост тюнинга XGB")
            ax.bar(x + 0.15, tune["family_gap_xgb_mlp"], width=0.3, label="|XGB default − MLP|")
            ax.set_xticks(x)
            ax.set_xticklabels(tune["dataset"], rotation=25, ha="right")
            ax.set_title("Тюнинг vs выбор семейства (упрощённо)")
            ax.legend()
            fig.tight_layout()
            fig.savefig(FIG_DIR / "tuning_vs_family.png", dpi=150)
            plt.close(fig)

    summary = {
        "n_datasets_ok": int(meta.shape[0]),
        "errors": errors,
        "meta": meta.to_dict(orient="records"),
        "tune": tune.to_dict(orient="records"),
        "results_head": results.head(20).to_dict(orient="records") if not results.empty else [],
    }
    (OUT_DIR / "run_summary.json").write_text(json.dumps(summary, ensure_ascii=False, indent=2))
    print("\nSaved results to", OUT_DIR)
    return results, meta, tune, errors


if __name__ == "__main__":
    main()
