function insertionSort(numbers: number[]): number[] {
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

const coolNums = [
  1, 33, 45, 22, 11, 99, 4, 2, 4, 5, 6, 3333, 555, 222, 34, 4, 5, 5, 6,
];

console.log(`
            My cool numbers are ${coolNums}
            My sorted cool numbers are ${insertionSort(coolNums)}
            `);
