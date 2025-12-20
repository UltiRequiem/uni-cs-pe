.data
origen:	.word 231400, 702540, 891300, 550600, 881900, 235100, 760555
destino:.word 0, 0, 0, 0, 0, 0, 0
strori:	.asciiz "El listado de origen es : "
strdes:	.asciiz "El listado de destino es : "
salto:	.asciiz "\n"
coma:	.asciiz ", "

.text
.globl main
main:
    li $t0, 7       
    li $t1, 0          
    la $t2, origen   
    la $t3, destino    
loop:
    lw $t4, ($t2)     
    mul $t5, $t4, 25   
    sw $t5, ($t3)     

    addi $t2, $t2, 4   
    addi $t3, $t3, 4
    addi $t1, $t1, 1
    blt  $t1, $t0, loop

    li $v0, 4
    la $a0, strori
    syscall

    li $t1, 0
    la $t2, origen
print_ori:
    lw $t4, ($t2)
    li $v0, 1
    move $a0, $t4
    syscall

    li $v0, 4
    la $a0, coma
    syscall

    addi $t2, $t2, 4
    addi $t1, $t1, 1
    blt $t1, $t0, print_ori

    li $v0, 4
    la $a0, salto
    syscall

    li $v0, 4
    la $a0, strdes
    syscall

    li $t1, 0
    la $t3, destino
print_des:
    lw $t4, ($t3)
    li $v0, 1
    move $a0, $t4
    syscall

    li $v0, 4
    la $a0, coma
    syscall

    addi $t3, $t3, 4
    addi $t1, $t1, 1
    blt $t1, $t0, print_des

    li $v0, 10
    syscall
