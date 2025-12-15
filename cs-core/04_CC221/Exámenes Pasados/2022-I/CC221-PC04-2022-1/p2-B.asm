#Pregunta 2 // Chavez Joel
	.data 
lista:	.double 458.115, 434.411, 710.217, 775.179, 333.444, 111.33441, 830.122, 663.443
str:	.asciiz "El promedio del listado es: "
n:	.double 8.0

	.text
main:
	li $t0,8	# n elementos
	li $t1,0	# contador
	la $a1,lista
hallar_prom:
	ldc1 $f2,($a1)
	add.d $f12,$f12,$f2
	
	add $t1,$t1,1
	beq $t0,$t1,continua
	add $a1,$a1,8
	b hallar_prom
continua:
	l.d $f4,n
	div.d $f12,$f12,$f4
print:
	li $v0,4
	la $a0,str
	syscall
	li $v0,3
	syscall
end:
	li $v0,10	
	syscall