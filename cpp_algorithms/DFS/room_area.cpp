#include <iostream>
using namespace std;

int n, x, y, area;
char maze[12][12];
bool visited[12][12];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void dfs(int x, int y){
    visited[x][y] = true;
    area++;
    for(int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny] && maze[nx][ny] == '.'){
            dfs(nx, ny);
        }
    }
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> maze[i][j];
        }
    }
    cin >> x >> y;
    x--; y--;
    dfs(x, y);
    cout << area;
    return 0;
}