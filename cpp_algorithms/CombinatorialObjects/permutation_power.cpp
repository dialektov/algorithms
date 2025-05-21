#include <iostream>
#include <vector>

int main() {
    size_t n,x;
    std::cin >> n;
    bool check = 1;
    std::vector<size_t> v1(n+1);
    std::vector<size_t> v2(n+1);
    for (size_t i = 1; i <= n; ++i) {
        std::cin >> x;
        v1[i] = x;
        v2[i] = x;
        if (x != i) check = 0;
    }
    size_t count = 1;
    while (!check) {
        check = 1;
        for (size_t i = 1; i <= n; ++i) {
        v1[i] = v2[v1[i]];
        if (i != v1[i]) check = 0;
        }
        count += 1;
    }
    std::cout << count;
    return 0;
}
