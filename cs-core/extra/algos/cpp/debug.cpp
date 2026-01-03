#include <iostream>
#include <vector>

using namespace std;

int lower_bound_debug(const vector<int> &nums, int bound) {
  cout << "  lower_bound(" << bound << ") on array: ";
  for (int x : nums) cout << x << " ";
  cout << endl;

  int low = 0, high = nums.size() - 1;
  cout << "  Initial: low=" << low << ", high=" << high << endl;

  while (low < high) {
    int mid = low + (high - low) / 2;
    int val = nums[mid];
    cout << "  Step: low=" << low << ", high=" << high << ", mid=" << mid << ", val=" << val << endl;

    if (val >= bound) {
      high = mid;
      cout << "    val >= bound, set high = " << mid << endl;
    } else {
      low = mid + 1;
      cout << "    val < bound, set low = " << mid + 1 << endl;
    }
  }

  cout << "  Final: returning low = " << low << endl;
  return low;
}

int main() {
    cout << "=== Debugging Test Case: [1], target = 1 ===" << endl;
    vector<int> nums = {1};
    int target = 1;

    cout << "\nStep 1: Find leftIndex" << endl;
    auto leftIndex = lower_bound_debug(nums, target);

    cout << "\nStep 2: Find rightIndex" << endl;
    auto rightIndex = lower_bound_debug(nums, target + 1) - 1;

    cout << "\nResults:" << endl;
    cout << "leftIndex = " << leftIndex << endl;
    cout << "rightIndex = " << rightIndex << endl;

    if (leftIndex < nums.size() && nums[leftIndex] == target) {
        cout << "Found target at leftIndex, returning [" << leftIndex << ", " << rightIndex << "]" << endl;
    } else {
        cout << "Target not found, returning [-1, -1]" << endl;
    }

    return 0;
}