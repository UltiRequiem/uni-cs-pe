import sys
from queue import LifoQueue, Queue
import API
import location
import state

MAZE_WIDTH = 16
MAZE_HEIGHT = 16

# Seguimiento de la dirección global actual
# 0 = Norte, 1 = Este, 2 = Sur, 3 = Oeste
cur_direction = 0

# Seguimiento de la posición física global en el laberinto como [x, y], inicializada en [0, 0]
cur_position = [0, 0]

# Matriz 2D de objetos Location para almacenar datos de cada casilla del laberinto
maze = [[location.Location([i, j]) for j in range(0, MAZE_WIDTH)] for i in range(0, MAZE_HEIGHT)]

# Pila de ubicaciones para el seguimiento de puntos que pueden necesitar explorarse (DFS)
loc_stack = LifoQueue()

# Pila de direcciones para retroceder fácilmente al encontrar un callejón sin salida (DFS)
dir_stack = LifoQueue()

# Pila de acciones para procesar la secuencia óptima de movimientos hacia el objetivo
act_stack = LifoQueue()

# Cola para estados no explorados durante la búsqueda en anchura (BFS)
frontier = Queue()


# Actualiza la posición física global
# move_direction: -1 retrocede, 1 avanza (actualmente solo avanza)
def update_position(move_direction=1):
    global cur_position
    if cur_direction == 0:    # mirando hacia el norte
        cur_position[1] += move_direction
    elif cur_direction == 1:  # mirando hacia el este
        cur_position[0] += move_direction
    elif cur_direction == 2:  # mirando hacia el sur
        cur_position[1] -= move_direction
    elif cur_direction == 3:  # mirando hacia el oeste
        cur_position[0] -= move_direction


# Actualiza la dirección global (-1 gira a la izquierda, 1 gira a la derecha)
def update_direction(turn_direction):
    global cur_direction
    cur_direction = (cur_direction + turn_direction) % 4


# Devuelve una lista con el estado de muros alrededor de la casilla actual
# Salida: [norte, este, sur, oeste]
def get_walls():
    walls = [False, False, False, False]
    # muro al frente según la orientación actual
    walls[cur_direction] = API.wallFront()
    # muro a la derecha
    walls[(cur_direction + 1) % 4] = API.wallRight()
    # sin muro en la dirección por donde venimos
    walls[(cur_direction + 2) % 4] = False
    # muro a la izquierda
    walls[(cur_direction + 3) % 4] = API.wallLeft()
    # en la casilla de inicio [0,0], marcar el muro sur como presente
    if cur_position == [0, 0]:
        walls[2] = True
    return walls


# Marca una casilla como visitada (color verde y texto informativo)
def mark_visited_api(pos=None):
    if pos is None:
        pos = cur_position
    API.setColor(pos[0], pos[1], "G")
    API.setText(pos[0], pos[1], "visitado")


# Marca una casilla como parte de la solución (color azul y texto "Sol")
def mark_solution_api(pos=None):
    if pos is None:
        pos = cur_position
    API.setColor(pos[0], pos[1], "B")
    API.setText(pos[0], pos[1], "Sol")

# Marca una casilla explorada en BFS (color cian y texto "BFS")
def mark_bfs_api(pos=None):
    if pos is None:
        pos = cur_position
    API.setColor(pos[0], pos[1], "C")
    API.setText(pos[0], pos[1], "BFS")

# Marca una casilla en la retroalimentación de retroceso (color naranja y texto "back")
def mark_bktrk_api(pos=None):
    if pos is None:
        pos = cur_position
    API.setColor(pos[0], pos[1], "O")
    API.setText(pos[0], pos[1], "back")


# Escribe un mensaje en la consola de errores (para depuración)
def log(string):
    sys.stderr.write(f"{string}\n")
    sys.stderr.flush()


# Mueve al ratón hacia adelante y actualiza la posición creyente
def move_forward():
    API.moveForward()
    update_position(1)


# Gira a la izquierda y actualiza la dirección
def turn_left():
    API.turnLeft()
    update_direction(-1)


# Gira a la derecha y actualiza la dirección
def turn_right():
    API.turnRight()
    update_direction(1)


# Gira 180 grados mediante dos giros a la derecha
def turn_around():
    turn_right()
    turn_right()


# Apunta la orientación del ratón hacia una dirección específica
def set_dir(_dir):
    if _dir == cur_direction:
        return  # ya en la dirección deseada
    if _dir == (cur_direction + 1) % 4:
        turn_right()
        return
    if _dir == (cur_direction + 2) % 4:
        turn_right()
        turn_right()
        return
    # debe ser girar a la izquierda
    turn_left()


# Gira hacia una ubicación adyacente indicada por un objeto Location
def turn_toward(loc):
    _dir = cur_direction
    # misma columna: norte o sur
    if cur_position[0] == loc.position[0]:
        if cur_position[1] - loc.position[1] == 1:
            _dir = 2  # girar hacia el sur
        else:
            _dir = 0  # girar hacia el norte
    else:
        # misma fila: este u oeste
        if cur_position[0] - loc.position[0] == 1:
            _dir = 3  # girar hacia el oeste
        else:
            _dir = 1  # girar hacia el este
    set_dir(_dir)


# Mapea el laberinto usando DFS y llenado de pilas
def dfs_map_maze():
    cur_loc = maze[cur_position[0]][cur_position[1]]

    # Si no ha sido visitada la ubicación actual, regístrala
    if not cur_loc.visited:
        cur_loc.set_visited(True)
        cur_loc.set_walls(get_walls())
        mark_visited_api(cur_position)

        # Agrega ubicaciones adyacentes no visitadas y sin muro a la pila de exploración
        if not cur_loc.walls[0] and not maze[cur_position[0]][cur_position[1] + 1].visited:
            loc_stack.put(maze[cur_position[0]][cur_position[1] + 1])
        if not cur_loc.walls[1] and not maze[cur_position[0] + 1][cur_position[1]].visited:
            loc_stack.put(maze[cur_position[0] + 1][cur_position[1]])
        if not cur_loc.walls[2] and not maze[cur_position[0]][cur_position[1] - 1].visited:
            loc_stack.put(maze[cur_position[0]][cur_position[1] - 1])
        if not cur_loc.walls[3] and not maze[cur_position[0] - 1][cur_position[1]].visited:
            loc_stack.put(maze[cur_position[0] - 1][cur_position[1]])

    # Bucle para explorar la siguiente ubicación disponible
    while True:
        if loc_stack.empty():
            # Si la pila está vacía y no estamos en [0,0], retrocede hasta origen
            if cur_position != [0, 0]:
                set_dir((dir_stack.get() + 2) % 4)
                move_forward()
                dfs_map_maze()
            return
        next_loc = loc_stack.get()
        if not next_loc.visited:
            break

    # Si se puede mover a la próxima ubicación, gira y avanza; sino, retrocede y reintenta
    if cur_loc.can_move_to(next_loc):
        turn_toward(next_loc)
        dir_stack.put(cur_direction)
        move_forward()
    else:
        loc_stack.put(next_loc)
        set_dir((dir_stack.get() + 2) % 4)
        move_forward()
    dfs_map_maze()


# Búsqueda en anchura para encontrar la ruta más corta al centro del laberinto
def find_bfs_shortest_path():
    # Reinicia todas las casillas a no visitadas
    for i in range(MAZE_HEIGHT):
        for j in range(MAZE_WIDTH):
            maze[i][j].visited = False
    first_state = state.State(maze[0][0])
    frontier.put(first_state)

    # Recorre la cola hasta encontrar la casilla meta
    while not frontier.empty():
        next_state = frontier.get()
        maze[next_state.location.position[0]][next_state.location.position[1]].set_visited(True)
        mark_bfs_api(next_state.location.position)
        if next_state.is_goal():
            return next_state

        my_loc = next_state.location
        if not my_loc.walls[0]:
            north_loc = maze[my_loc.position[0]][my_loc.position[1] + 1]
        if not my_loc.walls[1]:
            east_loc = maze[my_loc.position[0] + 1][my_loc.position[1]]
        if not my_loc.walls[2]:
            south_loc = maze[my_loc.position[0]][my_loc.position[1] - 1]
        if not my_loc.walls[3]:
            west_loc = maze[my_loc.position[0] - 1][my_loc.position[1]]

        # Genera nuevos estados para cada dirección posible
        if not my_loc.walls[0] and my_loc.can_move_to(north_loc) and not north_loc.visited:
            north_state = state.State(north_loc, next_state, (0 - next_state.cur_dir) % 4, 0)
            frontier.put(north_state)
        if not my_loc.walls[1] and my_loc.can_move_to(east_loc) and not east_loc.visited:
            east_state = state.State(east_loc, next_state, (1 - next_state.cur_dir) % 4, 1)
            frontier.put(east_state)
        if not my_loc.walls[2] and my_loc.can_move_to(south_loc) and not south_loc.visited:
            south_state = state.State(south_loc, next_state, (2 - next_state.cur_dir) % 4, 2)
            frontier.put(south_state)
        if not my_loc.walls[3] and my_loc.can_move_to(west_loc) and not west_loc.visited:
            west_state = state.State(west_loc, next_state, (3 - next_state.cur_dir) % 4, 3)
            frontier.put(west_state)

# Ejecuta la ruta más corta encontrada, usando la pila de acciones para seguir el camino inverso
def execute_shortest_path(sol):
    # Retrocede desde el estado solución hasta el inicial acumulando acciones
    while sol.parent is not sol:
        act_stack.put(sol.action)
        mark_bktrk_api(sol.location.position)
        sol = sol.parent
    # Ejecuta las acciones almacenadas para ir desde el inicio al centro
    while not act_stack.empty():
        act = act_stack.get()
        mark_solution_api()
        if act == 1:
            turn_right()
        elif act == 3:
            turn_left()
        move_forward()


def main():
    log("Iniciando mapeo del laberinto...")
    dfs_map_maze()
    set_dir(0)
    solution = find_bfs_shortest_path()
    execute_shortest_path(solution)
    log("¡Fin!")

if __name__ == "__main__":
    main()
