#include <iostream>
#include <vector>

std::vector<std::vector<size_t>> rmq(size_t n) {
    size_t s = 1;
    size_t k = 0;
    while (s <= n) {
        s *= 2;
        k += 1;
    }
    std::vector<std::vector<size_t>> v(k,std::vector<size_t>(n,0));
    size_t x;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> x;
        v[0][i] = x;
    }
    s = 1;
    for (size_t i = 1; i < k; ++i) {
        for (size_t j = 0; j < n - i; ++j) {
            v[i][j] = std::min(v[i-1][j],v[i-1][j+s]);
        }
    s *= 2;
    }
    return v;
}

size_t min(std::vector<std::vector<size_t>>& v, size_t l, size_t r) {
    size_t x = r - l + 1;
    size_t s = 1;
    size_t k = 0;
    while (s <= x) {
        s *= 2;
        k += 1;
    }
    s /= 2;
    k -= 1;
    return std::min(v[k][l],v[k][r-s+1]);
}

int main() {
    size_t n,q,l,r,ans;
    std::cin >> n;
    auto v = rmq(n);
    ans = 0;
    std::cin >> q;
    for (size_t i = 0; i < q; ++i) {
        std::cin >> l >> r;
        ans += min(v,l,r);
    }
    std::cout << ans;
    return 0;
}