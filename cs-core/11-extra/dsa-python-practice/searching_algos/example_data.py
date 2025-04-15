import random
import string

# Generate random lists of numbers
nums_1 = [random.randint(1, 1000) for _ in range(50)]
nums_2 = [random.randint(-500, 500) for _ in range(75)]

nums = sorted(nums_1)
rn_num = random.choice(nums)

# Generate random lists of strings
strings_1 = [''.join(random.choices(string.ascii_lowercase, k=5)) for _ in range(30)]
strings_2 = [''.join(random.choices(string.ascii_letters, k=8)) for _ in range(40)]

if __name__ == "__main__":
    print("nums_1:", nums_1)
    print("nums_2:", nums_2)
    print("strings_1:", strings_1)
    print("strings_2:", strings_2)

