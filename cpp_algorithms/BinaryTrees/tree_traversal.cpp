#include <iostream>
#include <set>
#include <algorithm>


std::set<int> make_list() {
    std::set<int> list;
    while (true) {
        int num;
        std::cin >> num;
        if (num != 0) list.insert(num);
        else return list;
    }
}

int main() {
    auto n = make_list();
    for (auto i : n) {
        std::cout << i << std::endl;
    }
    return 0;
}
