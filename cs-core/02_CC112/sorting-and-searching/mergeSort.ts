function merge(left: number[], right: number[]) {
	const result: number[] = [];
	let leftIndex = 0;
	let rightIndex = 0;

	while (leftIndex < left.length && rightIndex < right.length) {
		const currentLeft = left[leftIndex];
		const currentRight = right[rightIndex];

		if (currentLeft <= currentRight) {
			result.push(currentLeft);
			leftIndex++;
			continue;
		}

		result.push(currentRight);
		rightIndex++;
	}

	while (leftIndex < left.length) {
		result.push(left[leftIndex]);
		leftIndex++;
	}

	while (rightIndex < right.length) {
		result.push(right[rightIndex]);
		rightIndex++;
	}

	return result;
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

const arr = [38, 27, 43, 3, 9, 82, 10];
console.log(mergeSort(arr));
