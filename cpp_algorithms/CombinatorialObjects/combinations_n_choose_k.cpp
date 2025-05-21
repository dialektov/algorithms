#include <iostream>
#include <vector>

void print_combinations(int n, int k) {
    std::vector<int> combination(k);
    for (int i = 0; i < k; ++i) {
        combination[i] = i + 1;
    }
    while (true) {
        for (int i = 0; i < k; ++i) {
            if (i > 0) std::cout << " ";
            std::cout << combination[i];
        }
        std::cout << std::endl;
        int i = k - 1;
        while (i >= 0 && combination[i] == n - k + i + 1) {
            --i;
        }
        if (i < 0) break;
        ++combination[i];
        for (int j = i + 1; j < k; ++j) {
            combination[j] = combination[j - 1] + 1;
        }
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;
    print_combinations(n, k);
    return 0;
}