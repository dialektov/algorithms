# Доклад НИС: When Do Neural Nets Outperform Boosted Trees on Tabular Data?

Материалы доклада для НИС «Анализ данных и искусственный интеллект».

## Статья

- **Название:** When Do Neural Nets Outperform Boosted Trees on Tabular Data?
- **Авторы:** McElfresh et al.
- **Площадка:** NeurIPS 2023 (Datasets & Benchmarks)
- **Ссылка:** https://arxiv.org/abs/2305.02997
- **Код авторов:** https://github.com/naszilla/tabzilla

## Файлы

| Файл | Описание |
|------|----------|
| `presentation.html` | Презентация с разбором статьи (открыть в браузере) |
| `experiment.ipynb` | Ноутбук с проверкой ключевых утверждений |
| `requirements.txt` | Зависимости для ноутбука |

## Как запустить ноутбук

```bash
pip install -r requirements.txt
jupyter notebook experiment.ipynb
```

Выводы ячеек уже сохранены; повторный запуск воспроизводит результаты (seed=42).

## Что проверяем в эксперименте

Упрощённая проверка тезисов статьи:

1. На «нерегулярных» (скошенных) табличных данных GBDT обычно сильнее MLP.
2. Лёгкий тюнинг GBDT часто даёт прирост, сопоставимый с выбором семейства моделей.
3. Простой baseline иногда близок к сильным методам.

Упрощения относительно статьи: меньше датасетов, меньше моделей, sklearn-MLP вместо ResNet/FT-Transformer, без TabPFN.
