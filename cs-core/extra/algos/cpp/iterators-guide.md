# C++ Iterators Guide

## What are Iterators?

**Iterators** are objects that point to elements in containers (like vectors,
arrays, lists). Think of them as "smart pointers" that know how to navigate
through collections.

```cpp
vector<int> nums = {10, 20, 30, 40};
//               ↑   ↑   ↑   ↑   ↑
//            begin  +1  +2  +3  end
```

## Basic Iterator Concepts

### Getting Iterators

```cpp
vector<int> nums = {10, 20, 30, 40};

auto begin_it = nums.begin();  // Points to first element (10)
auto end_it = nums.end();      // Points AFTER last element (invalid)
```

### Accessing Elements

```cpp
auto it = nums.begin();

cout << *it;        // Dereference: prints 10
cout << it[2];      // Array-style access: prints 30
```

### Moving Iterators

```cpp
auto it = nums.begin();

it++;              // Move to next element (now points to 20)
it += 2;           // Move forward 2 positions (now points to 40)
it--;              // Move backward 1 position (now points to 30)
```

## Iterator to Index Conversion

### The Magic Formula

```cpp
vector<int> nums = {10, 20, 30, 40};
auto it = nums.begin() + 2;    // Points to 30

int index = it - nums.begin(); // index = 2
```

**Why this works:**

- `nums.begin()` is position 0
- `it - nums.begin()` gives the distance = index

### Visual Example

```
nums:     [10, 20, 30, 40]
indices:   0   1   2   3

it = nums.begin() + 2;  // Points to position 2 (value 30)
index = it - nums.begin();  // 2 - 0 = 2 ✅
```

## Real Examples from Your Code

### Example 1: Finding Element

```cpp
vector<int> nums = {5, 7, 7, 8, 8, 10};
auto it = lower_bound(nums.begin(), nums.end(), 8);

if (it != nums.end()) {
    int index = it - nums.begin();  // index = 3
    int value = *it;                // value = 8
    cout << "Found " << value << " at index " << index << endl;
}
```

### Example 2: Your searchRange Function

```cpp
// Find first occurrence
auto leftIt = lower_bound(nums.begin(), nums.end(), target);
int leftIndex = leftIt - nums.begin();

// Find position after last occurrence
auto rightIt = lower_bound(nums.begin(), nums.end(), target + 1);
int rightIndex = rightIt - nums.begin() - 1;
```

## Iterator Types

### Random Access Iterators (Vector, Array)

```cpp
vector<int> nums = {1, 2, 3, 4};
auto it = nums.begin();

it += 3;           // ✅ Jump directly to position 3
it[2];             // ✅ Array-style access
int dist = it2 - it1;  // ✅ Calculate distance
```

### Other Iterator Types

```cpp
list<int> myList = {1, 2, 3, 4};  // Linked list
auto it = myList.begin();

it++;              // ✅ Move forward one step
// it += 3;        // ❌ Can't jump directly!
// it[2];          // ❌ No array access!
```

## Common Iterator Operations

### Checking if Found

```cpp
auto it = find(nums.begin(), nums.end(), target);

if (it != nums.end()) {
    // Found it!
    int index = it - nums.begin();
    int value = *it;
} else {
    // Not found
    cout << "Element not found" << endl;
}
```

### Iterating Through Container

```cpp
// Method 1: Traditional iterator loop
for (auto it = nums.begin(); it != nums.end(); ++it) {
    cout << *it << " ";
}

// Method 2: Range-based for (C++11+) - preferred!
for (int value : nums) {
    cout << value << " ";
}
```

## Iterator Safety Rules

### ✅ Safe Operations

```cpp
vector<int> nums = {1, 2, 3};
auto it = nums.begin();

if (it != nums.end()) {  // Always check bounds!
    cout << *it;         // Safe to dereference
}
```

### ❌ Dangerous Operations

```cpp
auto it = nums.end();
cout << *it;            // ❌ Undefined behavior! end() is invalid

auto it = nums.begin();
nums.push_back(99);     // ❌ May invalidate iterator!
cout << *it;            // ❌ Potentially invalid now
```

## STL Algorithms with Iterators

### Common STL Functions

```cpp
vector<int> nums = {5, 7, 7, 8, 8, 10};

// Find first occurrence of 8
auto it1 = find(nums.begin(), nums.end(), 8);

// Find first element >= 8
auto it2 = lower_bound(nums.begin(), nums.end(), 8);

// Find first element > 8
auto it3 = upper_bound(nums.begin(), nums.end(), 8);

// Convert all to indices
int index1 = it1 - nums.begin();  // 3
int index2 = it2 - nums.begin();  // 3
int index3 = it3 - nums.begin();  // 5
```

### Why STL Uses Iterators

```cpp
// Works with ANY container type!
template<typename Iterator>
Iterator my_lower_bound(Iterator begin, Iterator end, int target) {
    // Same algorithm works for vector, array, list, etc.
}

vector<int> vec = {1, 2, 3};
array<int, 3> arr = {1, 2, 3};
list<int> lst = {1, 2, 3};

my_lower_bound(vec.begin(), vec.end(), 2);  // ✅ Works
my_lower_bound(arr.begin(), arr.end(), 2);  // ✅ Works
my_lower_bound(lst.begin(), lst.end(), 2);  // ✅ Works
```

## Quick Reference

| Operation     | Syntax              | What it does               |
| ------------- | ------------------- | -------------------------- |
| Get iterator  | `nums.begin()`      | Points to first element    |
| Get end       | `nums.end()`        | Points after last element  |
| Dereference   | `*it`               | Get value at iterator      |
| Move forward  | `it++` or `++it`    | Next element               |
| Move backward | `it--` or `--it`    | Previous element           |
| Jump          | `it += n`           | Move n positions forward   |
| To index      | `it - nums.begin()` | Convert iterator to index  |
| Check valid   | `it != nums.end()`  | Check if iterator is valid |

## Memory Mental Model

```
vector<int> nums = {10, 20, 30, 40};

Memory:   [10][20][30][40]
           ↑   ↑   ↑   ↑   ↑
Positions: 0   1   2   3   4(end)

begin() → position 0
end()   → position 4 (invalid, but marks the end)

Iterator arithmetic:
- begin() + 2 → position 2 (value 30)
- (begin() + 2) - begin() → 2 - 0 = 2 (index)
```

Iterators are just a generalized way to navigate through data structures - once
you understand the pointer-like behavior, they become very intuitive!
