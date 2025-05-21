#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj, adj_rev;
vector<bool> visited;
vector<int> order, component;

void dfs1(int v) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v, int c) {
    component[v] = c;
    for (int u : adj_rev[v]) {
        if (component[u] == -1)
            dfs2(u, c);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    adj.resize(n + 1);
    adj_rev.resize(n + 1);
    visited.resize(n + 1);
    component.resize(n + 1, -1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i])
            dfs1(i);
    }

    int c = 0;
    for (int i = 0; i < n; i++) {
        int v = order[n - 1 - i];
        if (component[v] == -1)
            dfs2(v, ++c);
    }

    cout << c << "\n";
    for (int i = 1; i <= n; i++) {
        cout << component[i] << " ";
    }

    return 0;
}