# MIPS Assembly Exercise Solutions - Explanations

## Exercise 1: Multiple String Output

**Task:** Modify the given program to print three different strings on separate
lines:

- "Hola a todos"
- "Bienvenidos a MIPS"
- "Un procesador de 32 bits"

**Original Program Analysis:** The original program prints "Hola mundo" using
syscall 4 (print string).

**Solution Approach:**

- Define three separate string variables in `.data` section
- Use syscall 4 (print string) three times with different string addresses
- Include newline characters (`\n`) in strings for proper line separation

**Key Techniques Used:**

- `.asciiz` directive for null-terminated strings
- `la` (load address) instruction to load string addresses into `$a0`
- Sequential syscall usage for multiple outputs

## Exercise 2: Modified Syscall Examples

**Task:** Test each syscall example separately and modify:

- First example: Print value from register `$t0 = 1880330`
- Second example: Print character 'U' from register `$t1`

**Solution Approach:**

- Modified syscall 1 (print integer) to use value from `$t0` instead of
  immediate value
- Modified syscall 11 (print character) to use ASCII value of 'U' (85) from
  `$t1`
- Kept existing float and string examples unchanged for reference

**Key Techniques Used:**

- `li` (load immediate) for loading constants into registers
- `move` instruction for register-to-register data transfer
- Understanding different syscall codes:
  - syscall 1: print integer (argument in `$a0`)
  - syscall 11: print character (ASCII value in `$a0`)
  - syscall 2: print float (argument in `$f12`)
  - syscall 4: print string (address in `$a0`)

## Exercise 3: Enhanced Sum Program

**Task:** Modify the basic sum program (8 + 9) to display the message "El
resultado es :" before showing the result.

**Original Program Analysis:** The original program calculates 8 + 9 but only
exits without showing output.

**Solution Approach:**

- Add result message string in `.data` section
- Print message using syscall 4 before printing the numerical result
- Print the calculated sum using syscall 1
- Maintain the original calculation logic

**Key Techniques Used:**

- String definition and storage in data section
- Sequential output operations (string then integer)
- Proper use of `$a0` register for syscall arguments
- Register management for preserving calculated values

## Common Programming Patterns

### Basic Input/Output Pattern

1. Define messages in `.data` section
2. Load string address with `la` instruction
3. Set syscall code in `$v0` register
4. Place argument in appropriate register (`$a0` for most operations)
5. Execute with `syscall`

### Program Structure

- `.data` section: Contains all string constants and variables
- `.text` section: Contains executable instructions
- `.globl main`: Makes main function globally accessible
- Program termination: syscall 10 for clean exit

These exercises demonstrate fundamental MIPS assembly concepts including data
definition, system calls, register usage, and basic program structure.
