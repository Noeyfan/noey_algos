#include "../noey_algos"
#include <iostream>

int main() {
  heap<int> hp(std::vector<int>{ 1,2,3,4,5,6,7,8,9,10});
  std::cout << hp.front() << "\n";
  hp.pop();
  std::cout << hp.front() << "\n";
}
