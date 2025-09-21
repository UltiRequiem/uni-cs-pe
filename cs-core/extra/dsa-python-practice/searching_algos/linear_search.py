from example_data import nums, rn_num

def linear_search(numbers: list[int], target: int):
	for index, number in enumerate(numbers):
		if number == target:
			return index
	return -1

print(nums)
print(linear_search(nums, rn_num))
