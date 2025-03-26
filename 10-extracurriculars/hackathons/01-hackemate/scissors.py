import random

winning_combinations = {
    'rock': 'paper',
    'paper': 'scissor',
    'scissor': 'rock'
}


def game():
    while True:

        user_choice = input('Rock, paper, or scissor? ').lower()
        computer_choice = random.choice(['rock', 'paper', 'scissor'])

        print(f'Computer choice: {computer_choice}.')

        if winning_combinations[user_choice] == computer_choice:
            print('You win!')
            break

        print("Try again!")
        print()


if __name__ == '__main__':
    game()
