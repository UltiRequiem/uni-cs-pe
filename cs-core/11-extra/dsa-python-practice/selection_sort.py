from example_data import nums_1

def selection_sort(nums: list[int]) -> list[int]:
    for index in range(len(nums)):
        min_val = nums[index]
        min_index = index

        for j in range(index, len(nums)):
            candidate_min = nums[j]

            if candidate_min < min_val:
                min_val = candidate_min
                min_index = j

        nums[index], nums[min_index] = nums[min_index], nums[index]


print("Previous list: ", nums_1)

selection_sort(nums_1)

print("Sorted list: ",nums_1)
