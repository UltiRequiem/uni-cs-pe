.data
result_msg: .asciiz "El resultado es : "

.text
.globl main
main:
    li $t1, 8
    add $t0, $t1, 9

    li $v0, 4
    la $a0, result_msg
    syscall

    li $v0, 1
    move $a0, $t0
    syscall

    li $v0, 10
    syscall