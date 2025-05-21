#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

const int MAXN = 1205;
vector<int> g[MAXN];
int color[MAXN];
bool used[MAXN];
pair<int, int> a[MAXN];

bool dfs(int v, int c) {
    used[v] = true;
    color[v] = c;
    for (int to : g[v]) {
        if (!used[to]) {
            if (!dfs(to, 1 - c)) {
                return false;
            }
        } else if (color[to] == color[v]) {
            return false;
        }
    }
    return true;
}

bool check(double mid, int n) {
    for (int i = 0; i < n; ++i) {
        g[i].clear();
        used[i] = false;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (hypot(a[i].first - a[j].first, a[i].second - a[j].second) < mid) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i] && !dfs(i, 0)) {
            return false;
        }
    }
    return true;
}

int main() {

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }

    double l = 0, r = 1e9;
    for (int it = 0; it < 100; ++it) {
        double mid = (l + r) / 2;
        if (check(mid, n)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    check(l, n);
    cout << fixed << setprecision(15) << l/2 << "\n";
    for (int i = 0; i < n; ++i) {
        cout << color[i] + 1 << " ";
    }
    cout << "\n";

    return 0;
}
