#include "../noey_algos"

void test01()
{
  noey::mst g;
  g.add_vertex(0);
  g.add_vertex(1);
  g.add_vertex(2);
  g.add_vertex(3);
  g.add_vertex(4);
  g.add_vertex(5);
  g.add_vertex(6);
  g.add_vertex(7);
  g.add_vertex(8);

  g.add_edge(0, 1, 4);
  g.add_edge(0, 7, 8);
  g.add_edge(1, 2, 8);
  g.add_edge(1, 7, 11);
  g.add_edge(7, 8, 7);
  g.add_edge(7, 6, 1);
  g.add_edge(8, 6, 6);
  g.add_edge(2, 8, 2);
  g.add_edge(2, 5, 4);
  g.add_edge(2, 3, 7);
  g.add_edge(3, 4, 9);
  g.add_edge(3, 5, 14);
  g.add_edge(6, 5, 2);
  g.add_edge(5, 4, 10);

  std::cout << g;
  std::cout << "result: \n";

  auto ret = g.prim_mst();
  for (const auto& ele : ret) {
      std::cout << ele.first << " " << ele.second << "\n";
  }
}

int main() {
  test01();
}
