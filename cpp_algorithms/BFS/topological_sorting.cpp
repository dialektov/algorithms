#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> tin, low;
int timer;
vector<bool> isArticulation;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p != -1)
                isArticulation[v] = true;
            ++children;
        }
    }
    if (p == -1 && children > 1)
        isArticulation[v] = true;
}

int main() {
    int n, m;
    cin >> n >> m;
    adj.resize(n + 1);
    visited.resize(n + 1);
    tin.resize(n + 1);
    low.resize(n + 1);
    isArticulation.resize(n + 1, false);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i])
            dfs(i);
    }

    vector<int> articulationPoints;
    for (int i = 1; i <= n; i++) {
        if (isArticulation[i])
            articulationPoints.push_back(i);
    }

    cout << articulationPoints.size() << "\n";
    for (int v : articulationPoints) {
        cout << v << endl;
    }

    return 0;
}