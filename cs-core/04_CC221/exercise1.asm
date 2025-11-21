.data
str1: .asciiz "Hola a todos\n"
str2: .asciiz "Bienvenidos a MIPS\n"
str3: .asciiz "Un procesador de 32 bits\n"

.globl main
.text
main:
    li $v0, 4
    la $a0, str1
    syscall

    li $v0, 4
    la $a0, str2
    syscall

    li $v0, 4
    la $a0, str3
    syscall

    li $v0, 10
    syscall