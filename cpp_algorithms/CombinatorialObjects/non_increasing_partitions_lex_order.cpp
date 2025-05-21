#include <iostream>
#include <vector>

void print_vector(const std::vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << " ";
        std::cout << v[i];
    }
    std::cout << std::endl;
}

void generate_partitions(int n, int max, std::vector<int>& current) {
    if (n == 0) {
        print_vector(current);
        return;
    }
    for (int i = 1; i <= std::min(n, max); ++i) {
        current.push_back(i);
        generate_partitions(n - i, i, current);
        current.pop_back();
    }
}

void print_sums(size_t n) {
    std::vector<int> current;
    generate_partitions(n, n, current);
}

int main() {
    size_t n;
    std::cin >> n;
    print_sums(n);
    return 0;
}
