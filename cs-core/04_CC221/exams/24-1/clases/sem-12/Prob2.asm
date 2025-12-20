	.data
origen: 	.double 16450.897, 70540.132, 89130.654, 55600.765, 88900.345, 25100.564, 23555.545
destino:	.double 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
mens1:  .asciiz "\nEl listado de origen es : "
mens2:  .asciiz "\nEl listado de destino es : "
multiplicar:  .double 537.167

	.text
    li $t0, 7              
    li $t1, 0              
    la $t2, origen         
    la $t3, destino        
    l.d $f4, multiplicar     

bucle:
    add $t2, $t2, 8       
    add $t3, $t3, 8       
    add $t1, $t1, 1
    ldc1 $f0, ($t2)      
    mul.d $f2, $f0, $f4   
    s.d $f2, ($t3)             
    bne $t1, $t0, bucle   

imp_origen:
    li $v0, 4              
    la $a0, mens1
    syscall
    li $t1, 0
    la $t2, origen

bucle_ori:
    add $t2, $t2, 8
    add $t1, $t1, 1    
    ldc1 $f0, ($t2)       
    li $v0, 3              
    mov.d $f12, $f0
    syscall
    li $v0, 11
    la $a0, ','
    syscall   
    bne $t1, $t0, bucle_ori

imp_destino:
    li $v0, 4              
    la $a0, mens2
    syscall
    li $t1, 0
    la $t3, destino

bucle_des:
    ldc1 $f0, ($t3)       
    li $v0, 3             
    mov.d $f12, $f0
    syscall
    li $v0, 11
    la $a0, ','
    syscall
    addi $t3, $t3, 8       
    addi $t1, $t1, 1      
    bne $t1, $t0, bucle_des 

Fin:
    li $v0, 10             
    syscall
