#include <algorithm> // For std::lower_bound
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> searchRange(const vector<int> &nums, int target) {
  if (nums.empty())
    return {-1, -1};

  // Find first occurrence using STL lower_bound
  auto leftIt = lower_bound(nums.begin(), nums.end(), target);

  // Check if target exists
  if (leftIt == nums.end() || *leftIt != target) {
    return {-1, -1};
  }

  // Find first position after target using STL lower_bound
  auto rightIt = lower_bound(nums.begin(), nums.end(), target + 1);

  // Convert iterators to indices
  int leftIndex = leftIt - nums.begin();
  int rightIndex = rightIt - nums.begin() - 1;

  return {leftIndex, rightIndex};
}

void runTest(vector<int> nums, int target, pair<int, int> expected) {
  auto result = searchRange(nums, target);

  cout << "Input: [";
  for (int i = 0; i < nums.size(); i++) {
    cout << nums[i];
    if (i < nums.size() - 1)
      cout << ",";
  }
  cout << "], target = " << target << endl;

  cout << "Expected: [" << expected.first << "," << expected.second << "]"
       << endl;
  cout << "Got:      [" << result.first << "," << result.second << "]" << endl;

  if (result == expected) {
    cout << "✅ PASS" << endl;
  } else {
    cout << "❌ FAIL" << endl;
  }
  cout << "-------------------" << endl;
}

int main() {
  cout << "Using STL std::lower_bound" << endl;
  cout << "=========================" << endl;

  vector<int> nums1 = {5, 7, 7, 8, 8, 10};
  runTest(nums1, 8, {3, 4});

  vector<int> nums2 = {5, 7, 7, 8, 8, 10};
  runTest(nums2, 6, {-1, -1});

  vector<int> nums3 = {};
  runTest(nums3, 0, {-1, -1});

  vector<int> nums4 = {1};
  runTest(nums4, 1, {0, 0});

  vector<int> nums5 = {2, 2, 2, 2};
  runTest(nums5, 2, {0, 3});

  return 0;
}
