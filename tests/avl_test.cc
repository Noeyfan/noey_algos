#include "../noey_algos"

void test01() {
  noey::avl_tree<int> avl(1);
  for (int i = 2; i <= 1000; ++i) {
    avl.insert(i);
  }

  avl.print();
}

int main() {
  test01();
}
