	.data
mens:	.asciiz "El resultado es : "
nums:	.double 123456.7698, 789000.9879, 887766.6545
multiplicar:	.double 25.767
dividir:		.double 3250.543
acum: 	.double 0.0

	.text
	
	li $t0, 3	#cantidad en la lista
	li $t1, 0            
	la $a1, nums	#lista
	la $a2, acum  
	l.d $f4, multiplicar       
	l.d $f6, dividir  
	
	
	
bucle:
	ldc1 $f8, ($a2)
	add $t1, $t1, 1
	ldc1 $f2,($a1)
	mul.d $f2, $f2, $f4
	div.d $f2,$f2,$f6
	add.d $f8,$f8,$f2
	s.d $f8, ($a2)
	addi $a1, $a1, 8 
	bne $t1, $t0, bucle
	b imprimir
	jr $ra

imprimir:
	li $v0,4
	la $a0,mens
	syscall
	li $v0,3
	ldc1 $f12, ($a2)
  	syscall
  	li $v0, 10          
   	syscall	
