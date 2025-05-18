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

void dfs(size_t now, std::vector<std::vector<size_t>>& graph, std::vector<bool>& visited, std::vector<int>& colors, std::string& answer) {
    visited[now] = true;
    for (size_t neig : graph[now]) {
        if (!visited[neig]) {
            colors[neig] = -colors[now];
            dfs(neig, graph, visited, colors, answer);
        } else if (colors[neig] == colors[now]) {
            answer = "NO";
        }
    }
}

int main() {
    size_t v;
    size_t e;
    std::cin >> v >> e;
    std::vector<std::vector<size_t>> graph = adj_list(v, e);
    std::vector<bool> visited(v + 1, false);
    std::vector<int> colors(v + 1, 0);
    std::string answer = "YES";
    for (size_t i = 1; i <= v; ++i) {
        if (!visited[i]) {
            size_t now = i;
            colors[i] = 1;
            dfs(now, graph, visited, colors, answer);
            if (answer == "NO") {
                break;
            }
        }
    }
    std::cout << answer;
    return 0;
}