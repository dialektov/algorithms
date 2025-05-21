#include <iostream>

void print_binary(size_t n) {
  for (int i = 0; i < (1 << n); ++i) {
    std::string s;
    for (int j = n - 1; j >= 0; --j) {
      if ((i >> j) & 1) {
        s += '1';
      } else {
        s += '0';
      }
    }
    std::cout << s << std::endl;
  }
}

int main() {
    size_t n;
    std::cin >> n;
  print_binary(n);
  return 0;
}
