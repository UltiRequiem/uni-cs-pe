.data
str1:   .asciiz "Ingresar un numero real : "
str2:   .asciiz "El resultado obtenido es : "
div:    .double 12.4769

.text
    li $v0, 4
    la $a0, str1
    syscall

    li $v0, 7  
    syscall

    mul.d $f6, $f0, $f0     
    mul.d $f6, $f6, $f0      
    mul.d $f6, $f6, $f0     
    mul.d $f6, $f6, $f0     

    ldc1 $f2, div           
    div.d $f4, $f6, $f2     

    li $v0, 4
    la $a0, str2
    syscall

    mov.d $f12, $f4
    li $v0, 3                
    syscall

end:
    li $v0, 10
    syscall
