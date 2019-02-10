#include "/Users/fanyou/src/algorithm/noey_algos"
#define INF 999999
#include <vector>
#include <queue>
using namespace std;

// O(|E| + |V|log(|V|))

// pair of to_node and weight
vector<int> dijkstra(const vector<vector<pair<int, int>>>& g, int s) {
  int N = g.size();

  // init distance
  vector<int> dist(N, INF);
  dist[s] = 0;

  // optional: init path tracking
  // vector<int> edge(N);

  // init queue, pair of weight and to_node
  priority_queue<pair<int, int>> q;
  q.push({dist[s], s}); // can also add all V here with INF dist

  while(!q.empty()) {
      const auto& [weight, from] = q.top();
      q.pop();
      // can check and return here if known target

      for (const auto& [to, toWeight] : g[from]) {
          // relax edge
          if (dist[to] > toWeight + weight) {
              dist[to] = toWeight + weight;
              // ideally we should use decrease quque,
              // but c++ priority_queue doesn't support,
              // so use additional memory here.
              q.push({dist[to], to});

              // optional: path tracking
              // edge[to] = from;
          }
      }
  }

  return dist;
}

int main() {
    for (int dis : dijkstra({{{1, 5}, {2, 100}}, {{2, 6}}, {}}, 0)) {
	cout << dis << "\n";
    }
    return 0;
}
