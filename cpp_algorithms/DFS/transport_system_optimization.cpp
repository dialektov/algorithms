#include <iostream>
#include <vector>
#include <queue>

using namespace std;

pair<int, int> bfs(int start, vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> distance(n, -1);
    queue<int> q;
    
    q.push(start);
    distance[start] = 0;
    
    int maxDistance = 0;
    int maxNode = start;
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        for (int neighbor : graph[curr]) {
            if (distance[neighbor] == -1) {
                q.push(neighbor);
                distance[neighbor] = distance[curr] + 1;
                
                if (distance[neighbor] > maxDistance) {
                    maxDistance = distance[neighbor];
                    maxNode = neighbor;
                }
            }
        }
    }
    
    return {maxNode, maxDistance};
}

int main() {
    int n;
    cin >> n;
    
    vector<vector<int>> graph(n);
    
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }
    
    pair<int, int> p1 = bfs(0, graph);
    pair<int, int> p2 = bfs(p1.first, graph);
    
    cout << p2.second << endl;
    
    return 0;
}
