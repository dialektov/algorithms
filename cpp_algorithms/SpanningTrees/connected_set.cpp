#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>

struct Point {
    int x, y;
};

double dist(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }
    std::vector<std::vector<double>> d(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            d[i][j] = dist(points[i], points[j]);
        }
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a;
        --b;
        d[a][b] = d[b][a] = 0;
    }
    std::vector<double> min_d(n, 1e9);
    std::vector<bool> used(n, false);
    min_d[0] = 0;
    double result = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || min_d[j] < min_d[v])) {
                v = j;
            }
        }
        used[v] = true;
        result += min_d[v];
        for (int j = 0; j < n; ++j) {
            min_d[j] = std::min(min_d[j], d[v][j]);
        }
    }
    std::cout << std::fixed << std::setprecision(5) << result;
    return 0;
}
