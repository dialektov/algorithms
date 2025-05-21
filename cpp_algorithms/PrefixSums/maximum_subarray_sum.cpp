#include <iostream>
#include <vector>

int main() {
    size_t n;
    std::cin >> n;
    std::vector<long long> v(n);
    long long x;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> x;
        v[i] = x;
    }
    long long ans = v[1];
	long long sum = 0;
    long long null = 0;
    for (int r=0; r<n; ++r) {
        sum += v[r];
        ans = std::max(ans, sum);
        sum = std::max(sum, null);
    }
    std::cout << ans;
    return 0;
}