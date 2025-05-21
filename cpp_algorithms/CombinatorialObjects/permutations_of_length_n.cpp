#include <algorithm>
#include <iostream>
#include <vector>

void generate_permutations(int n) {
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        numbers[i] = i + 1;
    }
    for (int num : numbers) {
        std::cout << num;
    }
    std::cout << std::endl;
    while (next_permutation(numbers.begin(), numbers.end())) {
        for (int num : numbers) {
        std::cout << num;
        }
        std::cout << std::endl;
    }
}

int main() {
    int n;
    std::cin >> n;
    generate_permutations(n);
    return 0;
}