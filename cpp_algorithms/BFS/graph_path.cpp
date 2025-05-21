#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<size_t>> adj_list(size_t v) {
    std::vector<std::vector<size_t>> list(v + 1);
    for (size_t v1 = 1; v1 <= v; ++v1) {
        for (size_t v2 = 1; v2 <= v; ++v2) {
            bool e;
            std::cin >> e;
            if (e && v1 != v2) {
                list[v1].push_back(v2);
                list[v2].push_back(v1);
            }
            
        }
    }
    return list;
}

void bfs(size_t& now, std::vector<std::vector<size_t>>& graph, std::vector<size_t>& ways,
        std::vector<std::vector<size_t>>& vertices, std::vector<size_t>& from) {
    for (std::vector<size_t> length : vertices) {
        for (size_t v : length) {
            for (size_t neig : graph[v]) {
                if (ways[neig] > ways[v]+1) {
                    vertices[ways[v]+1].push_back(neig);
                    ways[neig] = ways[v]+1;
                    from[neig] = v;
                }
            }
        }
    }
}

int main() {
    size_t v;
    std::cin >> v;
    std::vector<std::vector<size_t>> graph = adj_list(v);
    size_t max = v;
    size_t v1;
    size_t v2;
    std::cin >> v1 >> v2;
    std::vector<size_t> ways(v+1, max);
    std::vector<size_t> from(v+1, max);
    std::vector<std::vector<size_t>> vertices(v+1);
    ways[v1] = 0;
    vertices[0].push_back(v1);
    bfs(v1, graph, ways, vertices, from);
    if (ways[v2] >= max) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << ways[v2] << std::endl;
        if (ways[v2] > 0) {
            std::vector<size_t> answer;
            size_t way = v2;
            while (way != v1) {
                answer.push_back(way);
                way = from[way];
            }
            answer.push_back(v1);
            std::reverse(answer.begin(), answer.end());
            for (size_t i : answer) {
                std::cout << i << " ";
            }
        }
    }
    return 0;
}
