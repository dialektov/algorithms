#include <iostream>
#include <vector>
#include <vector>
#include <algorithm>

std::pair<std::vector<std::vector<size_t>>,size_t> adj_list(size_t n) {
    std::vector<std::vector<size_t>> list(n + 1);
    size_t v1 = 0;
    for (size_t i = 1; i <= n; ++i) {
        size_t v;
        std::cin >> v;
        if (v == 0) v1 = i;
        else if (v != i) {
            list[v].push_back(i);
            list[i].push_back(v);
        }
    }
    return {list,v1};
}

void dfs(size_t now, std::vector<std::vector<size_t>>& graph, std::vector<bool>& visited, std::vector<size_t>& order) {
    order.push_back(now);
    visited[now] = true;
    for (size_t neig : graph[now]) {
        if (!visited[neig]) {
            dfs(neig, graph, visited, order);
        }
    }
    order.push_back(now);
}

int main() {
    size_t n,q,x1,x2;
    std::cin >> n;
    auto para = adj_list(n);
    auto graph = para.first;
    auto v1 = para.second;
    std::vector<bool> visited(n + 1, false);
    std::vector<size_t> order;
    dfs(v1, graph, visited,order);
    std::vector<size_t> first(n+1,10000000000);
    std::vector<size_t> last(n+1,0);
    size_t k = 0;
    for (auto i : order) {
        first[i] = std::min(first[i],k);
        last[i] = std::max(last[i],k);
        k += 1;
    }
    std::cin >> q;
    for (size_t j = 0; j < q; ++j) {
        std::cin >> x1 >> x2;
        if (first[x1] < first[x2] && last[x1] > first[x2]) std::cout << 1 << std::endl;
        else std::cout << 0 << std::endl;
    }
    return 0;
}