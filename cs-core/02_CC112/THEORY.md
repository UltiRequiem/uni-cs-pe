# Teoría del Curso: Fundamentos de Programación

## Conceptos Clave

### 1. Punteros y Memoria Dinámica
El manejo directo de memoria es fundamental en C++.
- **Punteros**: Variables que almacenan direcciones de memoria.
- **Memoria Dinámica**: Uso del *heap* para crear variables en tiempo de ejecución.
```cpp
int* ptr = new int; // Asignación
*ptr = 10;
delete ptr; // Liberación
```

### 2. Programación Orientada a Objetos (POO)
Paradigma basado en "objetos" que contienen datos y métodos.
- **Clase**: Plantilla para crear objetos.
- **Objeto**: Instancia de una clase.
- **Encapsulamiento**: Proteger datos (`private`, `public`).

### 3. Archivos (File I/O)
Persistencia de datos usando `fstream`.
- `ifstream`: Lectura.
- `ofstream`: Escritura.
- `fstream`: Lectura y escritura.

### 4. Estructuras de Datos Lineales
- **Arreglos Dinámicos**: Arreglos que pueden cambiar de tamaño.
- **Listas Enlazadas**: Nodos conectados por punteros.
