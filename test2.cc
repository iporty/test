#include <vector>

#include "test2.h"

int add_1(int a) {
  std::vector<int> b;
  for (int i = 1; i < 10; ++i) {
    b.push_back(i);
  }

  return a + b[5];
}
