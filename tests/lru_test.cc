#include "../noey_algos"
#include <iostream>

void test01() {
  noey::lru_cache cache(10);
  cache.set(0, 2);
  cache.set(1, 3);
  cache.set(2, 1);
  assert(cache.get(0) == 2);
  assert(cache.get(1) == 3);
  assert(cache.get(2) == 1);
  cache.set(3, 6);
  assert(cache.get(3) == 6);
  assert(cache.get(0) == -1);
  assert(cache.get(1) == 3);
  assert(cache.get(2) == 1);
}

void test02() {
  noey::lru_cache cache(10);
  cache.set(0, 2);
  cache.set(1, 3);
  cache.set(2, 1);
  assert(cache.get(2) == 1);
  assert(cache.get(1) == 3);
  assert(cache.get(0) == 2);
  cache.set(3, 6);
  assert(cache.get(3) == 6);
  //std::cout << cache.get(2) << "\n";
  assert(cache.get(2) == -1);
  assert(cache.get(1) == -1);
  assert(cache.get(0) == 2);
  //std::cout << cache.get(0) << "\n";
}

void test03() {
  noey::lru_cache cache(10);
  cache.set(0, 0);
  cache.set(1, 1);
  cache.set(2, 2);
  cache.set(1, 9);
  assert(cache.get(1) == 9);
  assert(cache.get(0) == -1);
  assert(cache.get(2) == -1);
}

void test04() {
  noey::lru_cache cache(10);
  cache.set(0, 0);
  cache.set(1, 1);
  cache.set(2, 2);

  cache.set(0, 1);
  cache.set(1, 9);
  assert(cache.get(1) == 9);
  assert(cache.get(0) == 1);
  assert(cache.get(2) == -1);
}

void test05() {
  noey::lru_cache cache(10);
  cache.set(0, 0);
  cache.set(1, 1);
  cache.set(2, 2);
}

int main() {
  //test01();
  //test02();
  //test03();
  //test04();
  test05();
}
