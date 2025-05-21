#include <iostream>
#include <vector>
#include <vector>
#include <algorithm>

std::vector<std::vector<size_t>> make_graph(const size_t& v) {
    std::vector<std::vector<size_t>> graph(v+1,std::vector<size_t>(v+1,0));
    for (size_t x = 1; x <= v; ++x) {
        for (size_t y = 1; y <= v; ++y) {
            size_t n;
            std::cin >> n;
            if (n == 0) {
                graph[x][y] = v;
            } else {
                graph[x][y] = 1;
            }
        }
    }
    return graph;
}

void floyd(size_t v, std::vector<std::vector<size_t>>& graph) {
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
    std::vector<std::vector<size_t>> graph = make_graph(v);
    floyd(v,graph);
    bool ans = 0;
    for (size_t x = 1; x <= v; ++x) {
        for (size_t y = 1; y <= v; ++y) {
            if (graph[x][y] < v && graph[y][x] < v) {
                ans = 1;
                break;
            }
        }
    }
    std::cout << ans;
    return 0;
}
