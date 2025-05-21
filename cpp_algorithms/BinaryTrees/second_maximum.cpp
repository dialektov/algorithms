#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int first_max = -100000;
    int second_max = -100000;
    while (n != 0) {
        if (n > first_max) {
            second_max = first_max;
            first_max = n;
        } else if (n < first_max && n > second_max) {
            second_max = n;
        }
        std::cin >> n;
    }
    std::cout << second_max;
    return 0;
}
