#include "../noey_algos"
#include <iostream>

void test01() {
  noey::skip_list<int> list(0, 100);
  for (int i = 0; i < 100; ++i) {
    list.insert(i);
  }
  assert(!list.empty());
  for (int i = 0; i < 100; ++i) {
    list.erase(i);
  }
  assert(list.empty());
}

void test02() {
  noey::skip_list<int> list(0, 100);
  for (int i = 0; i < 100; ++i) {
    list.insert(i);
  }
  for (int i = 0; i < 100; ++i) {
    list.find(i);
  }
}

int main() {
  test01();
  test02();
}
