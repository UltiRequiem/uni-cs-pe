def merge(left: list[int], right: list[int]) -> list[int]:
    result = []

    i = j = 0

    n, m = len(left), len(right)

    while i < n and j < m:
        a, b = left[i], right[j]

        if a > b:
            result.append(b)
            j += 1
        else:
            result.append(a)
            i += 1

    if i < n:
        result.extend(left[i:])

    if j < m:
        result.extend(right[j:])

    return result


def merge_sort(list: list[int]) -> list[int]:
    n = len(list)

    if n <= 1:
        return list

    mid_index = n // 2

    left = merge_sort(list[:mid_index])
    right = merge_sort(list[mid_index:])

    return merge(left, right)


my_list = [
    1,
    4,
    2,
    5,
    6,
    7,
    8,
]

print(f"""
      My list is {my_list}
      My merged list is: {merge_sort(my_list)}
      """)
