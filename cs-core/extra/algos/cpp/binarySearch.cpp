#include <iostream>
#include <vector>

using namespace std;

int binary_search(const vector<int> &nums, int target) {
  int size = nums.size();

  int low = 0;
  int high = size - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;
    int val = nums.at(mid);

    if (val == target) {
      return mid;
    }

    if (val > target) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return -1;
}

int main() {
  vector<int> nums;

  for (int i = 0; i < 100; i++) {
    nums.push_back(i);
  }

  int index35 = binary_search(nums, 35);

  if (index35 != -1) {
    cout << index35 << endl;
  }

  return 0;
}
