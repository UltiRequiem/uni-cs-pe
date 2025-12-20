# Eliaz Bobadilla 20244697E
 .data
cadena: .asciiz "Si cumplimos las 5S seremos exitosos."
mens1: .asciiz "La cadena es: "
mens2: .asciiz "\nLa cantidad de vocales es: "

 .text
 .globl main
main:
 li $v0, 4
 la $a0, mens1
 syscall

 li $v0, 4
 la $a0, cadena
 syscall

 la $t0, cadena
 li $t1, 0

revisar:
 lb $t2, ($t0)
 beqz $t2, resultado

 li $t3, 'a'
 beq $t2, $t3, es_vocal
 li $t3, 'e'
 beq $t2, $t3, es_vocal
 li $t3, 'i'
 beq $t2, $t3, es_vocal
 li $t3, 'o'
 beq $t2, $t3, es_vocal
 li $t3, 'u'
 beq $t2, $t3, es_vocal

 li $t3, 'A'
 beq $t2, $t3, es_vocal
 li $t3, 'E'
 beq $t2, $t3, es_vocal
 li $t3, 'I'
 beq $t2, $t3, es_vocal
 li $t3, 'O'
 beq $t2, $t3, es_vocal
 li $t3, 'U'
 beq $t2, $t3, es_vocal

 j siguiente

es_vocal:
 add $t1, $t1, 1

siguiente:
 add $t0, $t0, 1
 j revisar

resultado:
 li $v0, 4
 la $a0, mens2
 syscall

 li $v0, 1
 move $a0, $t1
 syscall

 li $v0, 10
 syscall
