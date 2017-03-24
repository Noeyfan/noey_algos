#include "../noey_algos"

void test01()
{
  noey::pool p(1000);
  assert(noey::match("c", noey::build_nfa("ab.b*c.|", &p)));
}

void test02()
{
  noey::pool p(1000);
  assert(noey::match("bbbbbbbbbbbbbba", noey::build_nfa("b*a.", &p)));
}

int main()
{
  test01();
  test02();
}
