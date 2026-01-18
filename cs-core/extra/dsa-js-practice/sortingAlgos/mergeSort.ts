function merge(left: number[], right: number[]): number[] {
  const result: number[] = [];

  let i = 0;
  let j = 0;

  while (i < left.length && j < right.length) {
    const a = left[i];
    const b = right[j];

    if (a < b) {
      result.push(a);
      i++;
    } else {
      result.push(b);
      j++;
    }
  }

  if (i < left.length) {
    for (let k = i; k < left.length; k++) {
      const current = left[k];
      result.push(current);
    }
  }

  if (j < right.length) {
    for (let k = j; k < right.length; k++) {
      const current = right[k];
      result.push(current);
    }
  }

  return result;
}

function mergeSort(list: number[]): number[] {
  if (list.length <= 1) return list;

  const midIndex = Math.floor(list.length / 2);

  const left = mergeSort(list.slice(0, midIndex));
  const right = mergeSort(list.slice(midIndex));

  return merge(left, right);
}

const myArray = [4, 5, 6, 3, 2, 222, 444, 4, 66, 33, 995];

console.log(`
            My array is ${myArray}
            My sorted array is ${mergeSort(myArray)}
            `);
