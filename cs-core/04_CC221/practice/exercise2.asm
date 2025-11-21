.text
.globl main
main:
    li $t0, 1880330
    li $v0, 1
    move $a0, $t0
    syscall

    li $v0, 11
    li $a0, 10
    syscall

    li $t1, 85
    li $v0, 11
    move $a0, $t1
    syscall

    li $v0, 11
    li $a0, 10
    syscall

    .data
    numero: .float 34.567901
    .text
    li $v0, 2
    lwc1 $f12, numero
    syscall

    li $v0, 11
    li $a0, 10
    syscall

    li $v0, 4
    la $a0, cadena
    syscall

    li $v0, 10
    syscall

.data
cadena: .asciiz "La tecnología es maravillosa"