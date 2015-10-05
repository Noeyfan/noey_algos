#include "../noey_algos"
#include <iostream>
#include <cassert>
#include <limits.h>


struct my_less {
  bool operator()(int* a, int* b) {
    return *a < *b;
  }
};

int main() {
  int a = INT_MAX;
  int b = 11;
  int c = 12;
  int d = 13;
  std::vector<int*> vec { &a, &b, &c, &d };
  noey::heap<int*, my_less> hp(vec);
  *(vec[0]) = 1;
  assert(*hp.top() == 11);
  hp.pop();
  assert(*hp.top() == 1);
}
