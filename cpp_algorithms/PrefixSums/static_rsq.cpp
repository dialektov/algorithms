#include <iostream>
#include <vector>

std::vector<size_t> make_vector(size_t n) {
    std::vector<size_t> v(n+1);
    size_t x;
    v[0] = 0;
    for (size_t i = 1; i <= n; ++i) {
        std::cin >> x;
        v[i] = v[i-1]+x;
    }
    return v;
}

std::vector<size_t> make_chain(size_t q, size_t x, size_t n) {
    std::vector<size_t> c(q*2);
    c[0] = x;
    for (size_t i = 1; i <= q*2-1; ++i) {
        c[i] = (c[i-1]*11173 + 1) %1000000007;
    }
    return c;
}

size_t give_sum(std::vector<size_t>& v, std::vector<size_t>& c, size_t q, size_t n) {
    size_t sum = 0;
    for (size_t i = 0; i < q; ++i) {
        sum += v[std::max(c[i*2]%n,c[i*2+1]%n)+1]-v[std::min(c[i*2]%n,c[i*2+1]%n)];
        sum %= 1000000007;
    }
    return sum;
}

int main() {
    size_t n,q,x;
    std::cin >> n;
    auto v = make_vector(n);
    std::cin >> q;
    std::cin >> x;
    auto c = make_chain(q,x,n);
    std::cout << give_sum(v,c,q,n);
    return 0;
}
