	.data
frase0: .asciiz "Ingrese un numero real : "
frase1: .asciiz "El numero ingresado es igual a "
frase2: .asciiz "El numero ingresado no es igual a "
numero_a_c: .double 2500.1234
	
	.text
	li $v0,4
	la $a0,frase0
	syscall
	li $v0,7
	syscall
	l.d $f2,numero_a_c
	c.eq.d $f2,$f0
	bc1t es_igual
	li $v0,4
	la $a0,frase2
	syscall
	b salta
es_igual:
	li $v0,4
	la $a0,frase1
	syscall
salta:
	mov.d $f12,$f2
	li $v0,3
	syscall
	
	li $v0,10
	syscall
