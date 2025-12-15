	.data
frase1: .asciiz "Ingrese primer numero real: "
frase2: .asciiz "Ingrese segundo numero real: "
res: 	.asciiz "El resultado de la suma de punto flotante: "

	.text
	li $v0,4
	la $a0,frase1
	syscall
	li $v0,7
	syscall
	mov.d $f2,$f0
	li $v0,4
	la $a0,frase2
	syscall
	li $v0,7
	syscall
	
	add.d $f12,$f2,$f0
	li $v0,4
	la $a0,res
	syscall
	li $v0,3
	syscall
	li $v0,10
	syscall