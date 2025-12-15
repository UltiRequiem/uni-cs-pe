import location

# Clase que representa un estado dentro del laberinto
class State:

    # loc: ubicación física de este estado, como lista [x, y] (valores enteros)
    # parent: referencia al estado anterior (adyacente) que generó este estado
    # action: acción que tomó el padre para llegar a este estado
    #   Puede ser:
    #     0: sin giro (avanzar directo),
    #     1: girar a la derecha,
    #     2: girar en U,
    #     3: girar a la izquierda,
    #    -1: acción nula (por defecto en el estado inicial)
    # cur_dir: dirección actual del ratón al estar en este estado (0: norte, 1: este, 2: sur, 3: oeste)
    def __init__(self, loc, parent=None, action=None, cur_dir=None):
        self.location = loc
        if parent is None:
            self.parent = self          # El estado inicial se referencia a sí mismo como padre
        else:
            self.parent = parent
        if action is None:
            self.action = -1           # Acción por defecto (-1) si no se especifica
        else:
            self.action = action
        if cur_dir is None:
            self.cur_dir = 0           # Dirección por defecto (0: norte)
        else:
            self.cur_dir = cur_dir

    # Establece una nueva ubicación para este estado
    def set_loc(self, loc):
        self.location = loc

    # Establece el estado padre (el que generó este estado)
    def set_par(self, par):
        self.parent = par

    # Establece la acción tomada desde el padre para llegar a este estado
    def set_act(self, act):
        self.action = act

    # Establece la dirección actual del ratón en este estado
    def set_cur_dir(self, cur_dir):
        self.cur_dir = cur_dir

    # Determina si este estado es uno de los estados meta (objetivos)
    def is_goal(self):
        # Los objetivos están en el centro del laberinto, en las celdas (7,7), (7,8), (8,7), (8,8)
        return self.location.position == [7, 7] or self.location.position == [7, 8] \
            or self.location.position == [8, 7] or self.location.position == [8, 8]

