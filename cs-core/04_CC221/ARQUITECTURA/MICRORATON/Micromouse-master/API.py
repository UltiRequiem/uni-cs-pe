import sys

# Excepción personalizada para indicar que el ratón ha chocado contra una pared
class MouseCrashedError(Exception):
    pass

# Función general para enviar comandos al simulador y recibir una respuesta si se requiere
def command(args, return_type=None):
    # Prepara la línea de comando para enviar al simulador
    line = " ".join([str(x) for x in args]) + "\n"
    sys.stdout.write(line)   # Escribe el comando en la salida estándar
    sys.stdout.flush()       # Fuerza el envío del comando inmediatamente

    # Si se espera una respuesta del simulador
    if return_type:
        response = sys.stdin.readline().strip()  # Lee la respuesta
        if return_type == bool:
            return response == "true"            # Convierte a booleano si se espera un booleano
        return return_type(response)             # Convierte al tipo deseado

# Devuelve el ancho del laberinto (número de columnas)
def mazeWidth():
    return command(args=["mazeWidth"], return_type=int)

# Devuelve la altura del laberinto (número de filas)
def mazeHeight():
    return command(args=["mazeHeight"], return_type=int)

# Devuelve True si hay una pared al frente del ratón
def wallFront():
    return command(args=["wallFront"], return_type=bool)

# Devuelve True si hay una pared a la derecha del ratón
def wallRight():
    return command(args=["wallRight"], return_type=bool)

# Devuelve True si hay una pared a la izquierda del ratón
def wallLeft():
    return command(args=["wallLeft"], return_type=bool)

# Intenta mover al ratón una celda hacia adelante
# Lanza una excepción si el movimiento provoca un choque
def moveForward():
    response = command(args=["moveForward"], return_type=str)
    if response == "crash":
        raise MouseCrashedError()

# Gira el ratón 90 grados a la derecha
def turnRight():
    command(args=["turnRight"], return_type=str)

# Gira el ratón 90 grados a la izquierda
def turnLeft():
    command(args=["turnLeft"], return_type=str)

# Establece que hay una pared en (x, y) en la dirección indicada
def setWall(x, y, direction):
    command(args=["setWall", x, y, direction])

# Elimina una pared en (x, y) en la dirección indicada
def clearWall(x, y, direction):
    command(args=["clearWall", x, y, direction])

# Establece un color para la celda en (x, y)
def setColor(x, y, color):
    command(args=["setColor", x, y, color])

# Elimina el color de la celda en (x, y)
def clearColor(x, y):
    command(args=["clearColor", x, y])

# Elimina todos los colores del laberinto
def clearAllColor():
    command(args=["clearAllColor"])

# Establece un texto en la celda (x, y)
def setText(x, y, text):
    command(args=["setText", x, y, text])

# Elimina el texto de la celda (x, y)
def clearText(x, y):
    command(args=["clearText", x, y])

# Elimina todos los textos del laberinto
def clearAllText():
    command(args=["clearAllText"])

# Devuelve True si el simulador ha sido reiniciado desde la última vez que se comprobó
def wasReset():
    return command(args=["wasReset"], return_type=bool)

# Confirma al simulador que se ha detectado el reinicio
def ackReset():
    command(args=["ackReset"], return_type=str)
