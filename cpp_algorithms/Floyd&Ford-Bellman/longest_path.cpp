#include <iostream>
#include <vector>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> make_graph(const size_t& v) {
    std::vector<std::vector<int>> graph(v+1,std::vector<int>(v+1,0));
    for (size_t x = 1; x <= v; ++x) {
        for (size_t y = 1; y <= v; ++y) {
            int n;
            std::cin >> n;
            graph[x][y] = n;
        }
    }
    return graph;
}

void floyd(size_t v, std::vector<std::vector<int>>& graph) {
    for (size_t k = 1; k <= v; ++k) {
        for (size_t from = 1; from <= v; ++from) {
            for (size_t to = 1; to <= v; ++to) {
                graph[from][to] = std::min(graph[from][to], graph[from][k] + graph[k][to]);
            }
        }
    }
}

int main() {
    size_t v;
    std::cin >> v;
    auto graph = make_graph(v);
    floyd(v,graph);
    size_t ans = 0;
    for (size_t x = 1; x <= v; ++x) {
        for (size_t y = 1; y <= v; ++y) {
            if (graph[x][y] > ans) {
                ans = graph[x][y];
            }
        }
    }
    std::cout << ans;
    return 0;
}