# Teoría del Curso: Arquitectura de Computadores

## Conceptos Clave

### 1. Lenguaje Ensamblador (Assembly)

Lenguaje de bajo nivel que tiene una correspondencia directa con las
instrucciones de la máquina.

- **Registros**: Pequeñas unidades de almacenamiento en la CPU (e.g., `$t0`,
  `$a0` en MIPS; `A`, `B`, `R0-R7` en 8051).
- **Instrucciones**: Operaciones básicas (`MOV`, `ADD`, `JMP`).

### 2. Microcontrolador 8051

Arquitectura clásica de 8 bits.

- **Memoria de Programa (ROM)** y **Memoria de Datos (RAM)** separadas
  (Harvard).
- **Puertos I/O**: P0, P1, P2, P3 para conectar periféricos.
- **Timers/Counters**: Para medir tiempo o contar eventos.

### 3. Arquitectura MIPS

Arquitectura RISC (Reduced Instruction Set Computer).

- **Load/Store Architecture**: Solo las instrucciones de carga y almacenamiento
  acceden a memoria.
- **Pipeline**: Ejecución simultánea de múltiples instrucciones en diferentes
  etapas.

### 4. Interrupciones

Mecanismo por el cual un evento externo o interno detiene temporalmente el
programa principal para ejecutar una rutina de servicio (ISR).
