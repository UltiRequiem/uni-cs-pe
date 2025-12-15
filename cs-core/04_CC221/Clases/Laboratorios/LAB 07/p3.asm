##Area = pi.r.r
	.data
frase1: .asciiz "Ingrese el  radio del circulo "
frase2: .asciiz "El aera del circulo es: "
const_pi: .double 3.1415926535897932384626433832795
	.text
	li $v0,4
	la $a0,frase1
	syscall
	li $v0,7
	syscall
	l.d $f4,const_pi
	mul.d $f12,$f0,$f4		##pi x r
	mul.d $f12,$f0,$f12		##pi x r x r
	li $v0,4
	la $a0,frase2
	syscall
	li $v0,3
	syscall
	li $v0,10
	syscall