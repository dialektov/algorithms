#include <iostream>
#include <vector>

std::vector<std::pair<int,size_t>> segment_tree(const size_t n) {
    std::vector<std::pair<int,size_t>> tree(n * 2);
    int x;
    for (size_t i = n; i < n * 2; ++i) {
        std::cin >> x;
        tree[i] = {x,i};
    }
    for (size_t i = n-1; i > 0; --i) {
        tree[i] = std::max(tree[i * 2], tree[i * 2 + 1]);
    }
    return tree;
}

void update(std::vector<std::pair<int,size_t>>& tree, const size_t n, const size_t k, const int x) {
    size_t pos = n+k;
    tree[n+k] = {x,n+k};
    while (pos > 0) {
        pos = pos / 2;
        tree[pos] = std::max(tree[pos * 2], tree[pos * 2 + 1]);
    }
}

std::pair<int,size_t> max(std::vector<std::pair<int,size_t>>& tree, const size_t n, size_t l, size_t r) {
    l += n;
    r += n;
    std::pair<int,size_t> ans = tree[l];
    while (l <= r) {
        if (l % 2 != 0) ans = std::max(tree[l],ans);
        if (r % 2 == 0) ans = std::max(tree[r],ans);
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
            std::cout << max(tree,n,b,c).second - n << std::endl;
        }
    }
    return 0;
}
