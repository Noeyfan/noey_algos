#include "/Users/fanyou/src/algorithm/noey_algos"
#define INF 999999
#include <vector>
#include <queue>
using namespace std;

struct Edge {
  int to;
  int weight;
};

vector<int> spfa(const vector<vector<Edge>>& g, int s) {
  int N = g.size();
  vector<char> inqueue(N, false);
  vector<int> dis(N, INF);
  dis[s] = 0;
  inqueue[s] = true;
  queue<int> q;
  q.push(s);

  while(!q.empty()) {
    int cur = q.front(); q.pop();
    inqueue[cur] = false;

    for (Edge e : g[cur]) {
      int r = e.to;
      if (dis[r] > dis[cur] + e.weight) {
	dis[r] = dis[cur] + e.weight;
	if (!inqueue[r]) {
	  inqueue[r] = true;
	  q.push(r);
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
