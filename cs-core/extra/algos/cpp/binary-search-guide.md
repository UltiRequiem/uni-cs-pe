# Binary Search Algorithm Guide

## Core Binary Search Implementation

```cpp
int binary_search(const vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;  // Prevents overflow

        if (nums[mid] == target) return mid;
        if (nums[mid] > target) high = mid - 1;
        else low = mid + 1;
    }
    return -1;  // Not found
}
```

**Key Points:**
- Use `low + (high - low) / 2` to prevent integer overflow
- Condition: `while (low <= high)`
- Pass vectors by const reference for performance
- Time complexity: O(log n)

## Lower Bound Algorithm

**Definition:** Find the first position where `element >= target`

```cpp
int lower_bound(const vector<int>& nums, int bound) {
    int low = 0, high = nums.size();  // Note: size(), not size()-1

    while (low < high) {  // Note: <, not <=
        int mid = low + (high - low) / 2;

        if (nums[mid] >= bound) {  // >= not ==
            high = mid;  // Don't subtract 1!
        } else {
            low = mid + 1;
        }
    }
    return low;
}
```

**Key Differences from Binary Search:**
- `high = nums.size()` (exclusive upper bound)
- `while (low < high)`
- `if (nums[mid] >= target)` checks for >=
- `high = mid` (don't subtract 1)
- Always returns valid index (or size() if not found)

## Advanced: Find First and Last Position

**Problem:** Find range of target in sorted array
**Strategy:** Use lower_bound twice

```cpp
pair<int, int> searchRange(const vector<int>& nums, int target) {
    if (nums.empty()) return {-1, -1};

    auto leftIndex = lower_bound(nums, target);
    auto rightIndex = lower_bound(nums, target + 1) - 1;

    if (leftIndex < nums.size() && nums[leftIndex] == target) {
        return {leftIndex, rightIndex};
    }
    return {-1, -1};
}
```

**The Trick:**
- First occurrence: `lower_bound(target)`
- Last occurrence: `lower_bound(target + 1) - 1`

## C++ Best Practices

### Vector Access Methods
```cpp
// Safe but slower (bounds checking)
nums.at(i);  // Throws exception on out-of-bounds

// Fast but dangerous
nums[i];     // Undefined behavior on out-of-bounds
```

**Recommendation:** Use `.at()` for learning, `[]` for competitions

### Return Types
```cpp
// Production code - type safe
pair<int, int> searchRange(vector<int>& nums, int target);

// LeetCode style - dynamic
vector<int> searchRange(vector<int>& nums, int target);

// Also valid
tuple<int, int> searchRange(vector<int>& nums, int target);
```

**Best Practice:** Use `pair` for exactly 2 elements, `tuple` for more

### Namespace Usage
```cpp
// Learning/scripts - OK
using namespace std;

// Production/LeetCode - preferred
std::vector<int>, std::cout
```

## Common Gotchas

### Lower Bound Edge Cases
❌ **Wrong:** `high = nums.size() - 1`
✅ **Correct:** `high = nums.size()`

❌ **Wrong:** `while (low <= high)`
✅ **Correct:** `while (low < high)`

### Overflow Prevention
❌ **Dangerous:** `mid = (low + high) / 2`
✅ **Safe:** `mid = low + (high - low) / 2`

### Bounds Checking
Always validate array access:
```cpp
if (index < nums.size() && nums[index] == target) {
    // Safe to use index
}
```

## Algorithm Invariants

**Binary Search Invariant:**
- Target is in range [low, high] if it exists

**Lower Bound Invariant:**
- All elements left of `low` are `< target`
- All elements right of `high` are `>= target`
- When `low == high`, we found the boundary

## Testing Strategy

```cpp
void runTest(vector<int> nums, int target, pair<int, int> expected) {
    auto result = searchRange(nums, target);

    if (result == expected) {
        cout << "✅ PASS" << endl;
    } else {
        cout << "❌ FAIL" << endl;
    }
}
```

**Essential Test Cases:**
- Empty array
- Single element (found/not found)
- Multiple occurrences
- First/last element
- All same elements
- Not found

## Time Complexities

| Algorithm | Time | Space | Use Case |
|-----------|------|-------|----------|
| Binary Search | O(log n) | O(1) | Find exact match |
| Lower Bound | O(log n) | O(1) | Find insertion point |
| Linear Search | O(n) | O(1) | Verification only |