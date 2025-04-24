function merge(left: number[], right: number[]) {
  let sortedArr: number[] = [];

  while (left.length && right.length) {
    if (left[0] < right[0]) {
      sortedArr.push(left.shift()!);
    } else {
      sortedArr.push(right.shift()!);
    }
  }

  return [...sortedArr, ...left, ...right];
}

function mergeSort(nums: number[]): number[] {
  if (nums.length <= 1) {
    return nums;
  }

  const pivot = Math.floor(nums.length / 2);

  const left = mergeSort(nums.slice(0, pivot));
  const right = mergeSort(nums.slice(pivot));

  return merge(left, right);
}
