#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> prime_factors(int n) {
    std::vector<int> factors;
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }
    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 2)
        factors.push_back(n);
    return factors;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> factors = prime_factors(n);
    for (int factor : factors) {
        std::cout << factor << " ";
    }
    return 0;
}