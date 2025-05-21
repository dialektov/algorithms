#include <iostream>
#include <vector>

using namespace std;

vector<int> tree[100001];
int subtreeSize[100001];

void dfs(int node, int parent) {
    subtreeSize[node] = 1;
    for (int child : tree[node]) {
        if (child != parent) {
            dfs(child, node);
            subtreeSize[node] += subtreeSize[child];
        }
    }
}

int main() {
    int V;
    cin >> V;

    for (int i = 0; i < V - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(1, -1);

    for (int i = 1; i <= V; i++) {
        cout << subtreeSize[i] << " ";
    }

    return 0;
}