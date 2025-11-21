# Eliaz Bobadilla 20244697E
 .data
nums: .double 654321.3498, 900078.2479, 103721.4471, 997766.6545
mult: .double 12.167
div_num: .double 4750.133
cero: .double 0.0
mensaje: .asciiz "El resultado es : "

 .text
 .globl main
main:
 la $t0, nums
 l.d $f4, mult
 l.d $f6, div_num
 li $t1, 4

 l.d $f8, cero

bucle:
 l.d $f2, ($t0)

 mul.d $f2, $f2, $f4

 div.d $f2, $f2, $f6

 add.d $f8, $f8, $f2

 add $t0, $t0, 8
 add $t1, $t1, -1
 bnez $t1, bucle

 li $v0, 4
 la $a0, mensaje
 syscall

 li $v0, 3
 mov.d $f12, $f8
 syscall

 li $v0, 10
 syscall

# El resultado es : 6802.795971688182