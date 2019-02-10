#include "/Users/fanyou/src/algorithm/noey_algos"
#define INF 999999
#include <vector>
#include <queue>
using namespace std;

// best case O(|E|)
// worst case O(|E^2|)
// unstable

// pair of to_node and weight
vector<int> spfa(const vector<vector<pair<int, int>:>& g, int s) {
  int N = g.size();

  // init distance
  vector<int> dis(N, INF);
  dis[s] = 0;

  // optional: init path tracking
  // vector<int> edge(N);

  // init queue
  queue<int> q;
  q.push(s);

  // track inqueue status
  vector<char> inqueue(N, false);
  inqueue[s] = true;

  while(!q.empty()) {
    int from = q.front();
    q.pop();
    inqueue[from] = false;

    for (const auto& [to, weight] : g[from]) {
      // relax edge
      if (dis[to] > dis[from] + weight) {
	dis[to] = dis[from] + weight;
        // optional: path tracking
        // edge[to] = from;
	if (!inqueue[to]) {
	  inqueue[to] = true;
	  q.push(to);
	}
      }
    }
  }
  return dis;
}

int main() {
    for (int dis : spfa({{{1, 5}, {2, 100}}, {{2, 6}}, {}}, 0)) {
	cout << dis << "\n";
    }
    return 0;
}
