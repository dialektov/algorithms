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

std::pair<std::vector<int>,std::vector<size_t>> dijkstra(size_t& v, size_t& s, std::vector<std::vector<std::pair<size_t,int>>> graph) {
    std::vector<int> dist(v+1,-1);
    std::vector<size_t> last(v+1,0);
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
                last[neig.first] = now;
            } else if (dist[neig.first] > dist[now]+neig.second){
                dist[neig.first] = dist[now]+neig.second;
                last[neig.first] = now;
            }
        }
        visited[now] = 1;
    }
    return {dist, last};
}

int main() {
    size_t v,s,f;
    std::cin >> v >> s >> f;
    auto graph = adj_list(v);
    auto alg = dijkstra(v,s,graph);
    if (alg.first[f] == -1) std::cout << -1;
    else {
        std::vector<size_t> answer;
        answer.push_back(f);
        while (f != s) {
            answer.push_back(alg.second[f]);
            f = alg.second[f];
        }
        std::reverse(answer.begin(), answer.end());
        for (auto x : answer) std::cout << x << ' ';
    }
    return 0;
}
