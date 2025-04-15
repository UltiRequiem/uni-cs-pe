from example_data import nums_1

def insertion_sort(nums: list[int]) -> list[int]:
    n = len(nums)

    for index in range(1, n):
        value = nums[index]

        j = index - 1

      # Hasta que no le encontremos hogar,
      # vamos a hacer espacio!

        while j >= 0 and nums[j] > value:
            # correte uno mas alla,
            # no sabemos cuando nos 
            # detendremos!

            nums[j+1] = nums[j]
            j -= 1

        # Le encontramos hogar!!!
        nums[j+1] = value
        


print("Previous list: ", nums_1)

insertion_sort(nums_1)

print("Sorted list: ",nums_1)
