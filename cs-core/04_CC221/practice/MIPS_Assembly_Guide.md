# MIPS Assembly Programming Guide

## Overview

This document explains MIPS assembly language concepts and programming
techniques based on the provided laboratory exercises and solutions.

## Key MIPS Assembly Concepts

### 1. Program Structure

- `.data` section: Contains variables, strings, and constants
- `.text` section: Contains executable code
- `.globl main`: Makes main function globally accessible

### 2. System Calls (syscall)

MIPS uses system calls for input/output operations:

- `li $v0, 1`: Print integer (argument in $a0)
- `li $v0, 2`: Print float (argument in $f12)
- `li $v0, 3`: Print double (argument in $f12)
- `li $v0, 4`: Print string (address in $a0)
- `li $v0, 5`: Read integer (result in $v0)
- `li $v0, 6`: Read float (result in $f0)
- `li $v0, 7`: Read double (result in $f0)
- `li $v0, 8`: Read string (address in $a0, max length in $a1)
- `li $v0, 10`: Exit program
- `li $v0, 11`: Print character (ASCII value in $a0)

### 3. Register Usage

- `$t0-$t9`: Temporary registers
- `$v0-$v1`: Function return values and syscall codes
- `$a0-$a3`: Function arguments
- `$f0-$f31`: Floating point registers
- `$f12`: Floating point argument/return register

### 4. Memory Operations

- `la $reg, label`: Load address of label into register
- `lb $reg, offset($base)`: Load byte
- `lw $reg, offset($base)`: Load word
- `l.d $freg, offset($base)`: Load double
- `s.d $freg, offset($base)`: Store double

### 5. Control Flow

- `b label`: Unconditional branch
- `beq $r1, $r2, label`: Branch if equal
- `bne $r1, $r2, label`: Branch if not equal
- `bgt $r1, $r2, label`: Branch if greater than
- `bge $r1, $r2, label`: Branch if greater than or equal
- `ble $r1, $r2, label`: Branch if less than or equal
- `bnez $reg, label`: Branch if not equal to zero

### 6. Arithmetic Operations

- `add $rd, $rs, $rt`: Addition
- `sub $rd, $rs, $rt`: Subtraction
- `mul.d $fd, $fs, $ft`: Double precision multiplication
- `div.d $fd, $fs, $ft`: Double precision division
- `add.d $fd, $fs, $ft`: Double precision addition

### 7. Data Types

- `.asciiz "string"`: Null-terminated string
- `.space n`: Reserve n bytes of space
- `.word value`: 32-bit integer
- `.double value`: 64-bit floating point
- `.float value`: 32-bit floating point

## Programming Patterns

### String Length Calculation

```mips
li $t0, 0          # counter
la $t1, string     # string address
loop:
    lb $t2, ($t1)  # load byte
    bnez $t2, continue
    b done
continue:
    add $t0, $t0, 1    # increment counter
    add $t1, $t1, 1    # next character
    j loop
done:
```

### Array Processing

```mips
la $t0, array      # array address
li $t1, size       # array size
loop:
    lw $t2, ($t0)  # load element
    # process element
    add $t0, $t0, 4    # next element (4 bytes)
    add $t1, $t1, -1   # decrement counter
    bnez $t1, loop
```

### Input/Output Pattern

```mips
# Print prompt
li $v0, 4
la $a0, prompt
syscall

# Read input
li $v0, 5
syscall
move $t0, $v0      # save input

# Print result
li $v0, 4
la $a0, result_msg
syscall
li $v0, 1
move $a0, $t0
syscall
```

This guide covers the fundamental concepts needed to understand and write MIPS
assembly programs.
