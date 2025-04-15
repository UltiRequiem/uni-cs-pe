function insertionSort(numbers) {
  for (let i = 0; i < numbers.length; i++) {
    const key = numbers[i];
    let j = i - 1;

    while (j >= 0 && numbers[j] > key) {
      numbers[j + 1] = numbers[j];
      j--;
    }

    numbers[j + 1] = key;
  }

  return numbers;
}

const coolNums = [1, 4, 5, 6, 3333, 555, 222, 34, 4, 5, 5, 6];

console.log(coolNums);
console.log();
console.log(insertionSort(coolNums));
