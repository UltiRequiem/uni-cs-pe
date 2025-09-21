from example_data import nums, rn_num

def binary_search(nums: list[int], target: int):
	left, right = 0, len(nums) - 1

	# <= is important to check every case!!!
	while left <= right:
		mid = (left + right) // 2
		val = nums[mid]

		if val == target:
			return mid
		if val > target:
			right = mid -1
		else:
			left = mid + 1

	# return -1 if no element is found!!
	return -1
		


print(nums)
print(binary_search(nums, rn_num))
