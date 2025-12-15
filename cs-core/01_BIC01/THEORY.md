# Teoría del Curso: Introducción a la Computación

## Conceptos Clave

### 1. Estructura de un Programa en C++

Todo programa en C++ comienza con la función `main`. Es el punto de entrada.

```cpp
#include <iostream>

int main() {
    std::cout << "Hola Mundo" << std::endl;
    return 0;
}
```

### 2. Compilación

C++ es un lenguaje compilado. El código fuente (.cpp) se transforma en código
objeto y luego en un ejecutable.

- **Preprocesamiento**: Manejo de directivas como `#include`.
- **Compilación**: Traducción a ensamblador/código máquina.
- **Enlace (Linking)**: Combinación de archivos objeto y librerías.

### 3. Variables y Tipos

- `int` (enteros), `float`/`double` (decimales), `char` (caracteres), `bool`
  (booleanos).
- C++ es un lenguaje de tipado estático (se debe declarar el tipo).

### 4. Control de Flujo

- **Condicionales**: `if`, `else if`, `else`, `switch`.
- **Bucles**: `for` (iteraciones definidas), `while` (mientras se cumpla
  condición), `do-while`.

### 5. Funciones

Bloques de código reutilizables que realizan una tarea específica.

- **Declaración**: Firma de la función (tipo retorno, nombre, parámetros).
- **Definición**: El cuerpo de la función.
