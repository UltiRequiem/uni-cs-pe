# Eliaz Bobadilla 20244697E
 .data
origen: .double 26450.897, 93540.132, 99130.654, 77600.765, 99900.345, 25100.564, 23555.545
destino: .space 56
divisor: .double 137.129
mens_orig: .asciiz "Listado origen:\n"
mens_dest: .asciiz "\nListado destino:\n"
coma: .asciiz ", "

 .text
 .globl main
main:
 la $t0, origen
 la $t1, destino
 l.d $f6, divisor
 li $t2, 7

proceso:
 l.d $f2, ($t0)

 div.d $f2, $f2, $f6

 s.d $f2, ($t1)

 add $t0, $t0, 8
 add $t1, $t1, 8
 add $t2, $t2, -1
 bnez $t2, proceso

 li $v0, 4
 la $a0, mens_orig
 syscall

 la $t0, origen
 li $t2, 7
imprime_orig:
 li $v0, 3
 l.d $f12, ($t0)
 syscall

 add $t2, $t2, -1
 beqz $t2, salta_coma1

 li $v0, 4
 la $a0, coma
 syscall

salta_coma1:
 add $t0, $t0, 8
 bnez $t2, imprime_orig

 li $v0, 4
 la $a0, mens_dest
 syscall

 la $t1, destino
 li $t2, 7
imprime_dest:
 li $v0, 3
 l.d $f12, ($t1)
 syscall

 add $t2, $t2, -1
 beqz $t2, salta_coma2

 li $v0, 4
 la $a0, coma
 syscall

salta_coma2:
 add $t1, $t1, 8
 bnez $t2, imprime_dest

 li $v0, 10
 syscall
