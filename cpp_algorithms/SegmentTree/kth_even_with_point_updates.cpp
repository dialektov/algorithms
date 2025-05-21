#include <iostream>
#include <vector>

std::pair<std::vector<int>,std::vector<int>> segment_tree(const size_t l) {
    size_t n = 1;
    while (n < l) n *= 2;
    std::vector<int> tree(n * 2, 0);
    std::vector<int> list(l);
    int x;
    for (size_t i = n; i < n + l; ++i) {
        std::cin >> x;
        list[i-n] = x;
        tree[i] = (abs(x)+1)%2;
    }
    for (size_t i = n-1; i > 0; --i) {
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
    return {tree,list};
}

void update(std::vector<int>& tree, std::vector<int>& list, const size_t n, const size_t k, const int x) {
    size_t pos = n+k;
    list[k] = x;
    tree[n+k] = (abs(x)+1)%2;
    while (pos > 0) {
        pos = pos / 2;
        tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
    }
}

int sum(std::vector<int>& tree, const size_t n, size_t l, size_t r) {
    l += n;
    r += n;
    int ans = 0;
    while (l <= r) {
        if (l % 2 != 0) ans += tree[l];
        if (r % 2 == 0) ans += tree[r];
        l = (l + 1) / 2;
        r = (r - 1) / 2;
    }
    return ans;
}

size_t even(std::vector<int>& tree,const size_t n, int x, size_t v = 1) {
    if (x > tree[v]) return 0;
    if (v >= n) return v;
    if (x <= tree[v*2]) {
        return even(tree,n,x,v*2);
    }
    else return even(tree,n,x-tree[v*2],v*2+1);
}

int main() {
    size_t n,q;
    std::cin >> n;
    size_t N = 1;
    while (N < n) N*=2;
    auto para = segment_tree(n);
    auto tree = para.first;
    auto list = para.second;
    std::cin >> q;
    int a,b,c;
    for (size_t i = 0; i < q; ++i) {
        std::cin >> a;
        if (a == 2) {
            std::cin >> b >> c;
            update(tree,list,N,b,c);
        } else {
            std::cin >> b;
            auto k = even(tree,N,b);
            if (k == 0) {
                std::cout << "NONE" << std::endl;
            } else {
                std::cout << list[k-N] << std::endl;
            }
        }
    }
    return 0;
}