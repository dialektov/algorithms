#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> result;
bool cycle = false;
vector<char> color;

void dfs(int v) {
    color[v] = 'g';
    for (int u : adj[v]) {
        if (color[u] == 'w') {
            dfs(u);
        } else if (color[u] == 'g') {
            cycle = true;
        }
    }
    color[v] = 'b';
    result.push_back(v);
}

int main() {
    int n, m;
    cin >> n >> m;
    adj.resize(n + 1);
    visited.resize(n + 1);
    color.assign(n + 1, 'w');

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (color[i] == 'w') {
            dfs(i);
        }
    }

    if (cycle) {
        cout << -1;
    } else {
        reverse(result.begin(), result.end());
        for (int v : result) {
            cout << v << " ";
        }
    }

    return 0;
}