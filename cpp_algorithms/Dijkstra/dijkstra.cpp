#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

std::vector<std::vector<std::pair<size_t,int>>> adj_list(size_t v) {
    std::vector<std::vector<std::pair<size_t,int>>> list(v + 1);
    for (size_t v1 = 1; v1 <= v; ++v1) {
        for (size_t v2 = 1; v2 <= v; ++v2) {
            int e;
            std::cin >> e;
            if (e != -1 && v1 != v2) {
                list[v1].push_back({v2,e});
            }
        }
    }
    return list;
}

std::vector<int> dijkstra(size_t& v, size_t& s, std::vector<std::vector<std::pair<size_t,int>>> graph) {
    std::vector<int> dist(v+1,-1);
    std::vector<bool> visited(v+1,0);
    dist[s] = 0;
    for (size_t j = 0; j < v; ++j) {
        size_t min = -1;
        size_t now = 0;
        for (size_t i = 1; i <= v; ++i) {
            if (!visited[i] && (dist[i]<min || min == -1) && dist[i]!=-1) {
                now = i;
                min = dist[i];
            }
        }
        for (auto neig : graph[now]) {
            if (dist[neig.first] == -1) {
                dist[neig.first] = dist[now]+neig.second;
            } else {
                dist[neig.first] = std::min(dist[neig.first], dist[now]+neig.second);
            }
        }
        visited[now] = 1;
    }
    return dist;
}

int main() {
    size_t v,s,f;
    std::cin >> v >> s >> f;
    auto graph = adj_list(v);
    auto dist = dijkstra(v,s,graph);
    std::cout << dist[f];
    return 0;
}
