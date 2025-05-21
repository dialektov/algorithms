#include <iostream>

long long power(long long x, long long n, long long p) {
    long long res = 1;
    x = x % p;
    while (n > 0) {
        if (n & 1)
            res = (res * x) % p;
        n = n >> 1;
        x = (x * x) % p;
    }
    return res;
}

int main() {
    long long x, n, p;
    std::cin >> x >> n >> p;
    std::cout << power(x, n, p);
    return 0;
}