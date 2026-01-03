#include <iostream>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> searchRange(vector<int> &nums, int target) {
  // TODO: Implement using binary search
  // Find first and last position of target
  // Return [-1, -1] if not found
  return {-1, -1};
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
  cout << "LeetCode 34: Find First and Last Position of Element" << endl;
  cout << "====================================================" << endl;

  // Test case 1: Multiple occurrences
  vector<int> nums1 = {5, 7, 7, 8, 8, 10};
  runTest(nums1, 8, {3, 4});

  // Test case 2: Not found
  vector<int> nums2 = {5, 7, 7, 8, 8, 10};
  runTest(nums2, 6, {-1, -1});

  // Test case 3: Empty array
  vector<int> nums3 = {};
  runTest(nums3, 0, {-1, -1});

  // Test case 4: Single element found
  vector<int> nums4 = {1};
  runTest(nums4, 1, {0, 0});

  // Test case 5: Single element not found
  vector<int> nums5 = {1};
  runTest(nums5, 2, {-1, -1});

  // Test case 6: All same elements
  vector<int> nums6 = {2, 2, 2, 2};
  runTest(nums6, 2, {0, 3});

  // Test case 7: First element
  vector<int> nums7 = {1, 2, 3, 4, 5};
  runTest(nums7, 1, {0, 0});

  // Test case 8: Last element
  vector<int> nums8 = {1, 2, 3, 4, 5};
  runTest(nums8, 5, {4, 4});

  return 0;
}
