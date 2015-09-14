#ifndef NOEY_MST_CC
#define NOEY_MST_CC

#include <unordered_map>
#include <vector>
#include <iostream>
#include <utility>
#include <limits.h>
#include <functional>
#include "noey_heap.h"

namespace noey
{
  using std::pair;
  using std::vector;
  using std::unordered_map;
  using std::ostream;

  class __node
  {
    int _M_key, _M_wt;
    vector<__node*> _M_neighbours;
    bool _M_visited;

  public:
    __node(int __u = -1, int __w = INT_MAX)
    : _M_key(__u), _M_wt(__w), _M_visited(false)
    //Forgot to initialize the bool value, took whole night to debug QAQ
    { }

    ~__node() = default;

    int key() { return _M_key; }
    const int& key() const { return _M_key; }
    bool& visited() { return _M_visited; }
    const bool& visited() const { return _M_visited; }
    auto& neighbours() { return _M_neighbours; }
    const auto& neighbours() const { return _M_neighbours; }
    const int& weight() const { return _M_wt; }
    int& weight() { return _M_wt; }

    void add_neighbour(__node* __u)
    { _M_neighbours.push_back(__u); }

    operator bool() const
    { return this->_M_key == -1 ? false : true; }
  };

  //Prim's Minium Spanning Tree
  class __mst
  {
    struct __less
    {
      bool operator() (const __node* __u, const __node* __v)
      { return __u->weight() <= __v->weight(); }
    };

  public:
    //APIs
    __mst() = default;

    ~__mst()
    {
      for (__node* ele : _M_graph)
	delete ele;
    }

    void add_vertex(int __u)
    {
      _M_graph.push_back(new __node(__u));
      _M_edges.emplace_back();
    }

    void add_edge(int __u, int __v, int __w)
    {
      _M_graph[__u]->add_neighbour(_M_graph[__v]);
      _M_graph[__v]->add_neighbour(_M_graph[__u]);
      _M_edges[_M_graph[__u]->key()][_M_graph[__v]->key()] = __w;
      _M_edges[_M_graph[__v]->key()][_M_graph[__u]->key()] = __w;
    }

    auto& neighbours(int __u)
    { return _M_graph[__u]->neighbours(); }

    bool has_edge(int __u, int __v)
    { return _M_edges[_M_graph[__u]->key()][_M_graph[__v]->key()] != 0; }

    int weight(int __u, int __v)
    { return _M_edges[_M_graph[__u]->key()][_M_graph[__v]->key()]; }

    const auto graph() const
    { return _M_graph; }

    vector<pair<int, int>> prim_mst()
    {
      vector<pair<int, int>> __ret;
      __node foo;
      vector<__node*> parent(_M_graph.size(), &foo);
      if (_M_graph.empty()) return __ret;
      _M_graph[0]->weight() = 0;
      __heap<__node*, __less> hp(_M_graph);

      while(!hp.empty())
        {
          __node* min = hp.top();
          min->visited() = true;
          if (parent[min->key()]->key() != -1)
	    __ret.emplace_back(parent[min->key()]->key(), min->key());

          // update heap
          for (const auto& ele : min->neighbours())
            {
	      int weight_u_v = _M_edges[min->key()][ele->key()];
      	      __node* node = _M_graph[ele->key()];
      	      if (node->visited() == false && (node->weight() > weight_u_v))
		{
		  node->weight() = weight_u_v;
		  parent[node->key()] = min;
		}
	    }
          hp.pop();
        }
      return __ret;
    }

  private:
    vector<__node*> _M_graph;
    vector<unordered_map<int, int>> _M_edges;
  };

  ostream& operator<<(ostream& os, const __mst& mst) {
      for (const auto& ele : mst.graph())
	{
	  for (const auto& neg : ele->neighbours())
	    std::cout << neg->key() << " ";
	  std::cout << "\n";
	}
      return os;
  }
}

#endif
