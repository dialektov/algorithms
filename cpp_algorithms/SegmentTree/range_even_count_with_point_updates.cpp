#include <iostream>
#include <vector>

std::vector<int> segment_tree(const size_t n) {
    std::vector<int> tree(n * 2);
    int x;
    for (size_t i = n; i < n * 2; ++i) {
        std::cin >> x;
        tree[i] = (abs(x)+1)%2;
    }
    for (size_t i = n-1; i > 0; --i) {
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
    return tree;
}

void update(std::vector<int>& tree, const size_t n, const size_t k, const int x) {
    size_t pos = n+k;
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

int main() {
    size_t n,q;
    std::cin >> n;
    auto tree = segment_tree(n);
    std::cin >> q;
    int a,b,c;
    for (size_t i = 0; i < q; ++i) {
        std::cin >> a >> b >> c;
        if (a == 2) {
            update(tree,n,b,c);
        } else {
            std::cout << sum(tree,n,b,c) << std::endl;
        }
    }
    return 0;
}

