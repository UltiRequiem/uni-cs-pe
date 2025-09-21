table = [' ' for _ in range (0,9)]

winning_combinations = [
    [0,1,2], [3,4,5], [6,7,8],
    [0,3,6], [1,4,7], [2,5,8],
    [0,4,8], [2,4,6]
]

def check_winner(symbol):
    for combo in winning_combinations:
        if table[combo[0]] == table[combo[1]] == table[combo[2]] == symbol:
            return True

    return False

def graph_table():
    i = 0

    while i < 9:
        print(f'| ({table[i]}) ({table[i+1]}) ({table[i+2]}) |')
        i+=3

print('Las casillas estan numeradas del 1 al 9, comenzando por la izquierda superior.')

def play(user):
    position = int(input(f'(Jugador {user}) Escoge tu casilla: ')) - 1
    table[position] = user
    graph_table()
    
    if check_winner(user):
        print()
        print(f'Felicidades! Ganaste jugador {user}.')
        return True
    
    return False

while True:
    if play("x") or play("o"):
        break
