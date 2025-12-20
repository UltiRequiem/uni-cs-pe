#Pregunta 3 // Chavez Joel
	.data
coma:	.asciiz ", "
cte:	.double 4.653
lista:	.double 1234.443, 1341.112, 1789.371, 1455.229, 1234.551, 1999.124

	.text
main:
	li $t0,6	# n elementos
	li $t1,0	# contador
	la $a1,lista
	l.d $f4,cte
loop:
	ldc1 $f12,($a1)
	div.d $f12,$f12,$f4
	li $v0,3
	syscall
	
	add $t1,$t1,1
	beq $t0,$t1,end
	
	li $v0,4
	la $a0,coma
	syscall
	add $a1,$a1,8
	b loop
end:
	li $v0,10
	syscall