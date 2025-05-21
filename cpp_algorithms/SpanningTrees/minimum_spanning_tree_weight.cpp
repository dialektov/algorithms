#include <vector>
#include <algorithm>
#include <iostream>

struct Edge {
    int a, b, weight;
};

std::vector<int> parent, rank;

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            ++rank[a];
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    parent.resize(n);
    rank.resize(n);
    std::vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].a >> edges[i].b >> edges[i].weight;
        --edges[i].a;
        --edges[i].b;
    }
    std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });
    for (int i = 0; i < n; ++i)
        make_set(i);
    int result = 0;
    for (Edge e : edges) {
        if (find_set(e.a) != find_set(e.b)) {
            result += e.weight;
            union_sets(e.a, e.b);
        }
    }
    std::cout << result;
    return 0;
}
