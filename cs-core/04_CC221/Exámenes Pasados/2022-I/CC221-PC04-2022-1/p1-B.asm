#Pregunta 1 // Chavez Joel
	.data
str1:	.asciiz "Ingresar un primer número real : " 	
str2:	.asciiz "\nIngresar un segundo número real: "
str3:	.asciiz "\nDespués de las operaciones se obtiene : "
	
	 .text
	 li $v0,4
	 la $a0,str1
	 syscall
	 li $v0,7
	 syscall
	 mov.d $f2,$f0
	 
	 li $v0,4
	 la $a0,str2
	 syscall
	 li $v0,7
	 syscall
	 mov.d $f4,$f0
	 
	 sqrt.d $f2,$f2
	 sqrt.d $f4,$f4
	 sub.d $f12,$f2,$f4
	 mul.d $f12,$f12,$f12
	 
	 li $v0,4
	 la $a0,str3
	 syscall
	 li $v0,3
	 syscall
	 
	 li $v0,10
	 syscall
	 
	 