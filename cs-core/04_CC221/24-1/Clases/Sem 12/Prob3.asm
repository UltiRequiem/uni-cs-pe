	.data
inicio:	.asciiz "Ingrese la frase manualmente :"
mens:	.asciiz "La cantidad de consonantes es : "
	.text
	
	li $t2,0  #contador vocales
	li $t3,0	  #contador espacios
	li $t4,-1 #contador caracteres
	
	li $v0,4
	la $a0,inicio
	syscall
		
continua:
	li $v0,12
	syscall	
	move $t1,$v0
	jal is_vocal
	bne $t1,'\n',continua
	
	sub $t4,$t4,$t3
	sub $t4,$t4,$t2
	li $v0,4
	la $a0,mens
	syscall
	li, $v0,1
	move $a0,$t4
	syscall
	
Fin:
	li $v0,10	#servicio 10 indica el final de la ejecución del programa
	syscall
		
is_vocal:
	add $t4,$t4,1
	beq $t1,' ',inc_esp
	beq $t1,'.',inc_esp
	beq $t1,'a',inc_vol
	beq $t1,'e',inc_vol
	beq $t1,'i',inc_vol
	beq $t1,'o',inc_vol
	beq $t1,'u',inc_vol
	beq $t1,'A',inc_vol
	beq $t1,'E',inc_vol
	beq $t1,'I',inc_vol
	beq $t1,'O',inc_vol
	beq $t1,'U',inc_vol
	b sale
inc_vol:
	add $t2,$t2,1
	jr $ra
inc_esp:
	add $t3,$t3,1
	jr $ra
sale:
	jr $ra	#retorna de la subrutina