# Ejercicios Guiados - Asignación Dinámica con `new` y `delete` en C++ (Nivel Básico)

## Introducción

Estos ejercicios están diseñados para una introducción al uso de la asignación
dinámica de memoria en C++ usando `new` y `delete`.

---

## Ejercicio 1: Asignación dinámica de un solo entero

**Objetivo:** Aprender a usar `new` para asignar memoria para un entero y
`delete` para liberarla.

**Pasos:**

1. Crea un puntero a entero.
2. Usa `new` para asignar memoria dinámica.
3. Asigna un valor al entero apuntado.
4. Imprime ese valor.
5. Libera la memoria con `delete`.

---

## Ejercicio 2: Asignación dinámica de un arreglo de enteros

**Objetivo:** Reservar memoria para un arreglo usando `new[]` y liberarla con
`delete[]`.

**Pasos:**

1. Pide al usuario el tamaño del arreglo.
2. Usa `new` para crear un arreglo dinámico.
3. Llena el arreglo con valores.
4. Imprime los valores.
5. Usa `delete[]` para liberar la memoria.

---

## Ejercicio 3: Cambio de tamaño de un arreglo dinámico (simulación)

**Objetivo:** Simular el cambio de tamaño de un arreglo usando realocación
manual.

**Pasos:**

1. Crea un arreglo dinámico de `n` elementos.
2. Llena el arreglo con valores.
3. Crea un nuevo arreglo dinámico con tamaño mayor.
4. Copia los valores antiguos al nuevo arreglo.
5. Libera el arreglo original.
6. Asigna el puntero al nuevo arreglo.

---

## Ejercicio 4: Puntero a `float` dinámico

**Objetivo:** Usar `new` para asignar memoria a un `float`.

**Pasos:**

1. Declara un puntero a `float`.
2. Asigna memoria con `new`.
3. Asigna un valor decimal.
4. Muestra el valor.
5. Libera la memoria.

---

## Ejercicio 5: Asignación dinámica en una función

**Objetivo:** Devolver un puntero desde una función.

**Pasos:**

1. Crea una función que devuelva un puntero a entero.
2. Dentro de la función, usa `new` para asignar memoria.
3. Asigna un valor y retorna el puntero.
4. En `main`, llama a la función, imprime el valor.
5. Libera la memoria en `main`.

---

## Ejercicio 6: Memoria dinámica con estructuras

**Objetivo:** Usar `new` para crear dinámicamente una estructura.

**Pasos:**

1. Define una estructura `Persona` con nombre y edad.
2. Usa `new` para crear una `Persona`.
3. Asigna datos a sus campos.
4. Muestra la información.
5. Libera la memoria.

---

## Ejercicio 7: Arreglo dinámico de estructuras

**Objetivo:** Crear un arreglo dinámico de estructuras.

**Pasos:**

1. Define la estructura `Producto` con nombre y precio.
2. Pide al usuario cuántos productos desea ingresar.
3. Crea un arreglo dinámico.
4. Llena los datos.
5. Imprime los datos.
6. Libera la memoria.

---

## Ejercicio 8: Validar acceso a memoria después de `delete`

**Objetivo:** Entender qué ocurre si se accede a memoria liberada.

**Pasos:**

1. Asigna memoria con `new`.
2. Libera la memoria con `delete`.
3. Intenta acceder al valor (debería evitarse).
4. Observa el resultado y explica el comportamiento.

---

## Ejercicio 9: Inicialización de arreglos dinámicos

**Objetivo:** Inicializar arreglos dinámicos al momento de crearlos.

**Pasos:**

1. Crea un arreglo dinámico de 5 enteros.
2. Usa un bucle para asignar los valores de 1 a 5.
3. Imprime los valores.
4. Libera la memoria.

---

## Ejercicio 10: Doble puntero y memoria dinámica

**Objetivo:** Manejar doble puntero con memoria dinámica.

**Pasos:**

1. Declara un doble puntero (`int**`).
2. Usa `new` para asignar memoria para un puntero.
3. Luego, asigna memoria al entero apuntado.
4. Asigna un valor al entero.
5. Imprime el valor.
6. Libera ambas asignaciones (`delete` y `delete[]` si corresponde).

---

## Recomendaciones

- Siempre usa `delete` o `delete[]` para liberar memoria que ya no usas.
- No accedas a memoria después de liberarla.
- Considera usar `std::unique_ptr` en proyectos reales para manejo seguro de
  memoria.

# Ejercicios Guiados - Asignación Dinámica con `new` y `delete` en C++ (Nivel Intermedio)

## Introducción

Estos ejercicios están diseñados para profundizar en el uso de memoria dinámica
en C++, abordando estructuras de datos más elaboradas y el uso combinado con
funciones, estructuras, arreglos y punteros dobles.

---

## Ejercicio 1: Función que crea un arreglo dinámico

**Objetivo:** Crear una función que devuelva un puntero a un arreglo dinámico.

**Pasos:**

1. Escribe una función que reciba un tamaño `n`.
2. Dentro de la función, asigna memoria para un arreglo de `n` enteros.
3. Llena el arreglo con múltiplos de 10.
4. Retorna el puntero.
5. En `main`, imprime el contenido y libera la memoria.

---

## Ejercicio 2: Estructura anidada con memoria dinámica

**Objetivo:** Crear estructuras con campos que usan memoria dinámica.

**Pasos:**

1. Define una estructura `Estudiante` con:
   - `char* nombre` (memoria dinámica)
   - `int edad`
2. Pide datos al usuario.
3. Asigna memoria para `nombre` usando `new char[]`.
4. Copia el nombre con `strcpy`.
5. Imprime y libera memoria.

---

## Ejercicio 3: Crear y llenar una matriz dinámica

**Objetivo:** Asignar una matriz (arreglo de arreglos) dinámicamente.

**Pasos:**

1. Pide al usuario las dimensiones `filas` y `columnas`.
2. Usa `new` para crear un arreglo de punteros.
3. Cada puntero debe apuntar a un arreglo dinámico de columnas.
4. Llena la matriz.
5. Imprime su contenido.
6. Libera la memoria (primero las filas, luego el arreglo principal).

---

## Ejercicio 4: Lista de punteros a objetos

**Objetivo:** Crear un arreglo dinámico de punteros a estructuras.

**Pasos:**

1. Define una estructura `Libro` con título y autor.
2. Crea un arreglo dinámico de punteros a `Libro`.
3. Usa `new` para crear cada objeto individualmente.
4. Llena los datos.
5. Imprime la lista.
6. Libera la memoria correctamente.

---

## Ejercicio 5: Copia profunda vs. copia superficial

**Objetivo:** Demostrar la diferencia entre copia superficial y profunda.

**Pasos:**

1. Crea una clase `Cadena` con un `char* buffer`.
2. Implementa un constructor con asignación dinámica.
3. Crea una función que copie un objeto (por valor).
4. Cambia el contenido de uno y observa los resultados.
5. Corrige usando una copia profunda.

---

## Ejercicio 6: Redimensionamiento dinámico de un arreglo

**Objetivo:** Implementar una función que "redimensiona" un arreglo dinámico.

**Pasos:**

1. Crea un arreglo dinámico de tamaño `n`.
2. Llénalo con datos.
3. Crea una función `redimensionar` que reciba el puntero, tamaño actual y nuevo
   tamaño.
4. Dentro, crea un nuevo arreglo, copia los valores, libera el viejo y devuelve
   el nuevo.
5. Prueba el proceso.

---

## Ejercicio 7: Manejando memoria con punteros dobles

**Objetivo:** Pasar punteros dobles a funciones para asignar memoria desde allí.

**Pasos:**

1. Crea una función que reciba `int** p`.
2. Dentro de la función, asigna memoria dinámica.
3. Asigna un valor.
4. Desde `main`, llama a la función y muestra el valor.
5. Libera la memoria en `main`.

---

## Ejercicio 8: Contador de palabras con memoria dinámica

**Objetivo:** Usar punteros y memoria dinámica para separar palabras.

**Pasos:**

1. Pide al usuario una frase.
2. Divide la frase en palabras.
3. Almacena cada palabra en memoria dinámica (`char*`).
4. Guarda todos los punteros en un arreglo dinámico de punteros.
5. Imprime las palabras y libera toda la memoria.

---

## Ejercicio 9: Clase que gestiona memoria

**Objetivo:** Crear una clase con constructor, destructor y `new/delete`.

**Pasos:**

1. Crea una clase `VectorEnteros` con:
   - Un `int* arreglo`
   - Un entero `tamaño`
2. En el constructor, asigna memoria.
3. En el destructor, libera la memoria.
4. Agrega una función `llenar()` y `mostrar()`.

---

## Ejercicio 10: Arreglo de cadenas dinámicas

**Objetivo:** Crear un arreglo de cadenas de texto, todo en memoria dinámica.

**Pasos:**

1. Pide al usuario cuántas palabras ingresará.
2. Crea un arreglo dinámico de punteros a `char`.
3. Para cada palabra, asigna memoria y almacénala.
4. Muestra todas las palabras.
5. Libera cada cadena y luego el arreglo.

---

## Recomendaciones

- Practica el orden correcto de liberación de memoria.
- Usa `valgrind` (en Linux) o depuradores para detectar pérdidas de memoria.
- Recuerda: cada `new` debe tener su correspondiente `delete`, y cada `new[]`,
  un `delete[]`.

# Ejercicios Guiados - Asignación Dinámica con `new` y `delete` en C++ (Nivel Avanzado)

## Introducción

En estos ejercicios aplicarás técnicas avanzadas de asignación dinámica en
contextos como listas enlazadas, árboles binarios, clases con reglas de los 5, y
administración segura de memoria. Se recomienda tener buen dominio de punteros,
clases, constructores y destructores.

---

## Ejercicio 1: Implementar una lista enlazada simple

**Objetivo:** Crear una lista enlazada de enteros usando memoria dinámica.

**Pasos:**

1. Define una estructura `Nodo` con un `int dato` y un puntero al siguiente
   nodo.
2. Implementa funciones para:
   - Insertar al final.
   - Mostrar la lista.
   - Liberar toda la memoria con `delete`.
3. Prueba agregando varios elementos.

---

## Ejercicio 2: Crear una clase con regla de los 5

**Objetivo:** Implementar una clase que gestione memoria con constructor,
destructor, copia y movimiento.

**Pasos:**

1. Crea una clase `Buffer` con un `char*` dinámico y un `int tamaño`.
2. Implementa:
   - Constructor
   - Destructor
   - Constructor copia
   - Operador de asignación copia
   - Constructor y asignación por movimiento
3. Prueba el comportamiento en `main`.

---

## Ejercicio 3: Árbol binario con nodos dinámicos

**Objetivo:** Implementar un árbol binario con inserciones dinámicas.

**Pasos:**

1. Define una estructura `Nodo` con `dato`, `izq`, y `der`.
2. Implementa una clase `ArbolBinario` que use `new` para insertar nodos.
3. Agrega funciones para:
   - Insertar recursivamente.
   - Recorrer en orden.
   - Liberar toda la memoria en postorden.

---

## Ejercicio 4: Implementar un vector dinámico tipo `std::vector`

**Objetivo:** Crear una clase que simule un vector dinámico.

**Pasos:**

1. La clase `VectorDinamico` debe contener:
   - `int* datos`
   - `int capacidad`, `int tamaño`
2. Implementa:
   - Constructor
   - Destructor
   - Función `agregar()`, que redimensiona si es necesario.
   - Función `mostrar()`
3. Usa `new` y `delete[]` correctamente.

---

## Ejercicio 5: Tabla de hash con listas dinámicas

**Objetivo:** Implementar una tabla hash simple con manejo de colisiones.

**Pasos:**

1. Crea una tabla como arreglo dinámico de punteros a listas.
2. Cada lista es una lista enlazada de claves (`int`).
3. Implementa:
   - Función hash.
   - Inserción.
   - Búsqueda.
4. Libera toda la memoria.

---

## Ejercicio 6: Arreglo tridimensional dinámico

**Objetivo:** Crear una estructura 3D usando punteros dinámicos.

**Pasos:**

1. Pide al usuario dimensiones (X, Y, Z).
2. Crea un arreglo de punteros a punteros a punteros (`int***`).
3. Asigna memoria dinámicamente en tres niveles.
4. Llena con datos.
5. Libera cada nivel correctamente.

---

## Ejercicio 7: Gestión dinámica de strings en una clase

**Objetivo:** Implementar una clase que administre memoria para múltiples
cadenas.

**Pasos:**

1. Crea la clase `Diccionario` que contiene un arreglo dinámico de `char*`.
2. Implementa funciones para:
   - Agregar palabra.
   - Mostrar palabras.
   - Eliminar palabra.
3. Administra correctamente la memoria en destructor.

---

## Ejercicio 8: Matriz dispersa dinámica

**Objetivo:** Representar una matriz dispersa utilizando nodos dinámicos.

**Pasos:**

1. Usa una lista enlazada para almacenar solo los elementos no cero.
2. Cada nodo contiene fila, columna y valor.
3. Implementa funciones para:
   - Insertar valor.
   - Buscar valor.
   - Imprimir matriz completa.
4. Libera memoria correctamente.

---

## Ejercicio 9: Uso de `new` y `delete` con plantillas

**Objetivo:** Crear una clase plantilla que gestione memoria dinámica para
cualquier tipo.

**Pasos:**

1. Crea una clase plantilla `Array<T>`.
2. Internamente usa `T* datos` y `int tamaño`.
3. Implementa:
   - Constructor
   - Destructor
   - Operador de acceso `[]`
4. Prueba con `int`, `float`, y objetos.

---

## Ejercicio 10: Simulador de archivos con buffers dinámicos

**Objetivo:** Simular el manejo de buffers como si fueran archivos.

**Pasos:**

1. Crea una clase `ArchivoVirtual` que tenga un `char* buffer` y un
   `int capacidad`.
2. Permite escribir al buffer, redimensionar si es necesario.
3. Permite leer y mostrar el contenido.
4. Usa `new` y `delete[]` correctamente.
5. Asegúrate de no provocar fugas de memoria.

---

## Recomendaciones Avanzadas

- Revisa la Regla de los 5 al trabajar con clases que usan `new`.
- Considera el uso de `std::unique_ptr` o `std::shared_ptr` para mayor
  seguridad.
- Usa herramientas como `valgrind` o sanitizers para detectar errores de
  memoria.
- Siempre libera la memoria en orden inverso al de su asignación.
