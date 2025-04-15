def vowel_count(text: str) -> int:
    vowels = ['a', 'e', 'i', 'o', 'u']

    count = 0
    for letter in text:
        if letter.lower() in vowels:
            count+=1

    return count

user_input = input('Ingrese el texto: ')
print(vowel_count(user_input))

