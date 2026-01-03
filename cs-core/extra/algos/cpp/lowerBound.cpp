#include <iostream>
#include <vector>

using namespace std;

int lower_bound(const vector<int> &nums, int target) {
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
  vector<int> nums;

  for (int i = 0; i < 100; i += 3) {
    nums.push_back(i);
  }

  int result = lower_bound(nums, 35);

  for (int i = 0; i < nums.size(); i++) {
    cout << nums.at(i) << " ";
  }

  cout << endl << "The index of the lower bound of 35 is " << result << endl;

  int trueLowerBound = 0;

  for (int i = 0; nums.at(i) < 35; i++) {
    cout << nums.at(i) << " ";
    trueLowerBound++;
  }

  cout << endl
       << "The expected lower bound of 35 is " << trueLowerBound << endl;

  return 0;
}
