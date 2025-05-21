#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

std::vector<std::vector<std::pair<size_t,size_t>>> adj_list(size_t k, size_t v) {
    std::vector<std::vector<std::pair<size_t,size_t>>> list(v + 1);
    for (size_t i = 1; i <= k; ++i) {
        size_t a,b,e;
        std::cin >> a >> b >> e;
        list[a].push_back({b,e});
        list[b].push_back({a,e});
    }
    return list;
}

std::vector<size_t> dijkstra(size_t& v, size_t& s, std::vector<std::vector<std::pair<size_t,size_t>>> graph) {
    std::vector<size_t> dist(v+1,30000000000000);
    std::set<std::pair<size_t,size_t>>set;
    for (size_t i = 1; i <= v; ++i) {
        if (i != s) set.insert({30000000000000,i});
    }
    set.insert({0,s});
    dist[s] = 0;
    for (size_t i = 0; i < v; ++i) {
        size_t now = set.begin()->second;
        for (auto neig : graph[now]) {
            if (dist[neig.first] > dist[now]+neig.second) {
                set.erase(set.find({dist[neig.first],neig.first}));
                dist[neig.first] = dist[now]+neig.second;
                set.insert({dist[neig.first],neig.first});
            }
        }
        set.erase(set.begin());
    }
    return dist;
}

int main() {
    size_t v,k;
    std::cin >> v >> k;
    auto graph = adj_list(k,v);
    size_t s,f;
    std::cin >> s >> f;
    auto dist = dijkstra(v,s,graph);
    if (dist[f] == 30000000000000) {
        std::cout << -1;
    } else {
        std::cout << dist[f];
    }
    return 0;
}