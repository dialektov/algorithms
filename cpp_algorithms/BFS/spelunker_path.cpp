#include <iostream>
#include <vector>
#include <algorithm>


void v_list(size_t& v, std::vector<std::vector<std::vector<bool>>>& list, std::vector<size_t>& s) {
    for (size_t v1 = 1; v1 <= v; ++v1) {
        for (size_t v2 = 1; v2 <= v; ++v2) {
            for (size_t v3 = 1; v3 <= v; ++v3) {
                char e;
                std::cin >> e;
                if (e == '.') {
                    list[v1][v2][v3] = 1;
                } else if (e == 'S') {
                    list[v1][v2][v3] = 1;
                    s = {v1, v2, v3};
                }
            }
        }
    }
}

std::vector<std::vector<size_t>> adj_list(size_t& v, std::vector<std::vector<std::vector<bool>>>& list) {
    std::vector<std::vector<size_t>> adj_list(v*v*v + 1);
    std::vector<int> x_shift = {-1,1,0,0,0,0};
    std::vector<int> y_shift = {0,0,-1,1,0,0};
    std::vector<int> z_shift = {0,0,0,0,-1,1};
    for (size_t v1 = 1; v1 <= v; ++v1) {
        for (size_t v2 = 1; v2 <= v; ++v2) {
            for (size_t v3 = 1; v3 <= v; ++v3) {
                if (list[v1][v2][v3]) {
                    for (size_t i = 0; i < 6; ++i) {
                        if (list[v1+x_shift[i]][v2+y_shift[i]][v3+z_shift[i]]) {
                            adj_list[v*v*(v1-1)+v*(v2-1)+v3].push_back(v*v*(v1+x_shift[i]-1)+v*(v2+y_shift[i]-1)+v3+z_shift[i]);
                            adj_list[v*v*(v1+x_shift[i]-1)+v*(v2+y_shift[i]-1)+v3+z_shift[i]].push_back(v*v*(v1-1)+v*(v2-1)+v3);
                        }
                    }
                }
            }
        }
    }
    return adj_list;
}

void bfs(size_t& now, std::vector<std::vector<size_t>>& graph, std::vector<size_t>& ways, std::vector<std::vector<size_t>>& vertices) {
    for (std::vector<size_t> length : vertices) {
        for (size_t v : length) {
            for (size_t neig : graph[v]) {
                if (ways[neig] > ways[v]+1) {
                    vertices[ways[v]+1].push_back(neig);
                    ways[neig] = ways[v]+1;
                }
            }
        }
    }
}

int main() {
    size_t v;
    std::cin >> v;
    std::vector<std::vector<std::vector<bool>>> list(v  + 2, std::vector<std::vector<bool>>(v + 2, std::vector<bool>(v + 2, 0)));
    std::vector<size_t> s;
    v_list(v, list, s);
    std::vector<std::vector<size_t>> graph = adj_list(v, list);
    size_t max = v*v*v;
    std::vector<size_t> ways(v*v*v+1, max);
    std::vector<std::vector<size_t>> vertices(v*v*v+1);
    size_t now = v*v*(s[0]-1)+v*(s[1]-1)+s[2];
    ways[now] = 0;
    vertices[0].push_back(now);
    int answer = -1;
    bfs(now, graph, ways, vertices);
    for (size_t i = 0; i <= v*v*v; ++i) {
        for (size_t x : vertices[i]) {
            if (x <= v*v) {
                answer = i;
                break;
            }
        }
        if (answer != -1) {
            std::cout << answer;
            break;
        }
    }
    return 0;
}
