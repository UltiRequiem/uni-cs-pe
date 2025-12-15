##Grados Celsius = (F-32)x5/9
	.data
frase1: .asciiz "Ingrese la temperatura en grados Fahrenheit: "
frase2: .asciiz "La temperatura en grados Celsius es: "
grado: .asciiz "°C"
const32: .double 32
factor5_9: .double  0.5555555555555556
	.text
	li $v0,4
	la $a0,frase1
	syscall
	li $v0,7
	syscall
	l.d $f4,const32
	sub.d $f2,$f0,$f4		##F-32
	l.d $f4,factor5_9
	mul.d $f12,$f2,$f4		##(F-32)x5/9
	li $v0,4
	la $a0,frase2
	syscall
	li $v0,3
	syscall
	li $v0,4
	la $a0,grado
	syscall
	li $v0,10
	syscall
