#include <iostream>
#include <vector>
#include <vector>
#include <algorithm>
#include <iomanip>

std::vector<std::vector<float>> make_graph(const size_t& n, const size_t& m) {
    std::vector<std::vector<float>> graph(n+1,std::vector<float>(n+1,0));
    for (size_t i = 1; i <= m; ++i) {
        size_t from,to;
        float l;
        std::cin >> from >> to >> l;
        graph[from][to] = 1 - l/100;
        graph[to][from] = 1 - l/100;
    }
    return graph;
}

void floyd(size_t v, std::vector<std::vector<float>>& graph) {
    for (size_t k = 1; k <= v; ++k) {
        for (size_t from = 1; from <= v; ++from) {
            for (size_t to = 1; to <= v; ++to) {
                graph[from][to] = std::max(graph[from][to], graph[from][k]*graph[k][to]);
            }
        }
    }
}

int main() {
    size_t n,m;
    std::cin >> n >> m;
    size_t from,to;
    std::cin >> from >> to;
    auto graph = make_graph(n,m);
    floyd(n,graph);
    std::cout << std::fixed << std::setprecision(3) << 1 - graph[from][to];
    return 0;
}

