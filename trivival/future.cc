// Thread safe bucket division
// TODO: Possible improvment open
// a thread for each bucket to avoid mutex

#include <future>
#include <vector>
#include <mutex>

using namespace std;

// naive global lock
mutex vec_mutex;

int get_idx(int num) {
  while(num >= 10)
    num /= 10;
  return num;
}

bool
process_lock(vector<int>& vec,
	     vector<vector<int>>& res,
	     int start, int end) {
  for(int i = start; i < end; ++i) {
    int idx = get_idx(vec[i]), val = vec[i];
    lock_guard<mutex> lock(vec_mutex);
    res[idx].push_back(val);
  }
  return true;
}

vector<vector<int>>
process(vector<int>& vec, int thread_num) {
  vector<vector<int>> ret(10, vector<int>());
  int size = vec.size(), diff = size / thread_num;
  for(int i = 0; i < thread_num; ++i) {
    auto fut = async(launch::async, ref(process_lock),
		     ref(vec), ref(ret),
		     i * diff, i * diff + diff);
  }
  return ret;
}

#include <leetcode>
int main() {
  vector<int> vec {8, 20, 13, 15, 21, 23, 19, 17, 16,
      55, 44, 48, 32, 89, 91, 0, 64, 72, 83, 63};
  auto ret = process(vec, 4);
  cout << ret;
}
