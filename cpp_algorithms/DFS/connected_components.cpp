#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<size_t>> adj_list(size_t v, size_t e) {
    std::vector<std::vector<size_t>> list(v + 1);
    for (size_t i = 1; i <= e; ++i) {
        size_t v1;
        size_t v2;
        std::cin >> v1 >> v2;
        if (v1 != v2) {
            list[v1].push_back(v2);
            list[v2].push_back(v1);
        }
    }
    return list;
}

void dfs(size_t now, std::vector<std::vector<size_t>>& graph, std::vector<bool>& visited, std::vector<std::vector<size_t>>& answer) {
    visited[now] = true;
    answer[answer.size()-1].push_back(now);
    for (size_t neig : graph[now]) {
        if (!visited[neig]) {
            dfs(neig, graph, visited, answer);
        }
    }
}

int main() {
    size_t v;
    size_t e;
    std::cin >> v >> e;
    std::vector<std::vector<size_t>> graph = adj_list(v, e);
    std::vector<bool> visited(v + 1, false);
    std::vector<std::vector<size_t>> answer;
    for (size_t i = 1; i <= v; ++i) {
        if (!visited[i]) {
            size_t now = i;
            std::vector<size_t> comp;
            answer.push_back(comp);
            dfs(now, graph, visited, answer);
        }
    }
    std::cout << answer.size() << std::endl;
    for (std::vector<size_t> i : answer) {
        std::cout << i.size() << std::endl;
        for (size_t j : i) {
            std::cout << j << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}