// https://en.wikipedia.org/wiki/Dutch_national_flag_problem
#include <vector>
using namespace std;

void partition(vector<int>& input, int mid) {
    int i = 0, j = 0, k = input.size() - 1;

    while (j <= k) {
        if (input[j] < mid) {
            swap(input[j], input[i]);
            i++;
            j++;
        } else if (input[j] > mid) {
            swap(input[j], input[k]);
            k--;
        } else {
            ++j;
        }
    }
}

#include <iostream>
int main() {
    vector<int> A{3,1,2,1,2,3};
    partition(A, 2);
    for (int i : A) cout << i;
}
