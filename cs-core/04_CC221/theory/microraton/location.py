# Clase que representa una ubicación: contiene todos los datos asociados a un cuadrado del mapa
class Location:
    def __init__(self, pos=None):
        # Paredes en las 4 direcciones: [norte, este, sur, oeste]
        self.walls = [False, False, False, False]
        # Posición [x, y] del cuadrado
        self.position = [-1, -1]
        # Bandera que indica si esta ubicación ya fue visitada
        self.visited = False
        # Si se proporciona una posición inicial, se establece
        if pos is not None:
            self.position[0] = pos[0]
            self.position[1] = pos[1]

    # Establece la posición como una lista ordenada [x, y]
    def set_position(self, pos):
        self.position[0] = pos[0]
        self.position[1] = pos[1]

    # Establece el estado de las paredes: lista de 4 booleanos [norte, este, sur, oeste]
    def set_walls(self, walls):
        self.walls[0] = walls[0]
        self.walls[1] = walls[1]
        self.walls[2] = walls[2]
        self.walls[3] = walls[3]

    # Establece si la ubicación ha sido visitada (True o False)
    def set_visited(self, vis):
        self.visited = vis

    # Verifica si se puede mover desde esta ubicación a otra
    # Las ubicaciones deben ser adyacentes y no debe haber una pared entre ellas
    def can_move_to(self, loc):
        # loc está al norte y no hay pared al norte
        # o loc está al este y no hay pared al este
        # o loc está al sur y no hay pared al sur
        # o loc está al oeste y no hay pared al oeste
        return (loc.position[0] == self.position[0] and loc.position[1] - self.position[1] == +1 and not self.walls[0])\
            or (loc.position[1] == self.position[1] and loc.position[0] - self.position[0] == +1 and not self.walls[1])\
            or (loc.position[0] == self.position[0] and loc.position[1] - self.position[1] == -1 and not self.walls[2])\
            or (loc.position[1] == self.position[1] and loc.position[0] - self.position[0] == -1 and not self.walls[3])
