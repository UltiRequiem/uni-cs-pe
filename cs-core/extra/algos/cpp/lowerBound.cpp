#include <iostream>
#include <vector>

int lower_bound(const std::vector<int> &nums, int target) {
  int low = 0;
  int high = nums.size() - 1;

  while (low < high) {
    int mid = low + (high - low) / 2;
    int val = nums.at(mid);

    if (val >= target) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }

  return low;
}

int main() {
  std::vector<int> nums;
  auto target = 35;

  for (int i = 0; i < 100; i += 3) {
    nums.push_back(i);
  }

  int result = lower_bound(nums, target);

  for (int i = 0; i < nums.size(); i++) {
    std::cout << nums.at(i) << " ";
  }

  std::cout << std::endl
            << "The index of the lower bound of " << target << " is " << result
            << "." << std::endl;

  int trueLowerBound = 0;

  while (trueLowerBound < nums.size() && nums.at(trueLowerBound) < target) {
    trueLowerBound++;
  }

  std::cout << std::endl
            << "The expected lower bound of " << target << " is "
            << trueLowerBound << std::endl;

  return 0;
}
