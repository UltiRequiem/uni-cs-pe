.data
mayor:  .asciiz "El numero mayor del listado es : "
menor:  .asciiz "El numero menor del listado es : "
salto:  .asciiz "\n"

list:   .double 551845.8931, 725234.4311, 9526400.2176, 2221775.1796, 1011333.7743, 9990111.6677

.text
    li $t0,6               # total de elementos
    li $t1,1               # comenzamos desde el segundo
    la $a1,list
    ldc1 $f2,($a1)         # mínimo inicial
    ldc1 $f4,($a1)         # máximo inicial

loop:
    addi $a1,$a1,8         # siguiente elemento
    ldc1 $f6,($a1)         # leer valor actual

    c.lt.d $f6,$f2
    bc1t less

    c.lt.d $f4,$f6
    bc1t greater

next:
    addi $t1,$t1,1
    blt $t1,$t0,loop       # solo si aún no se llegó al final

print:
    li $v0,4
    la $a0,mayor
    syscall

    mov.d $f12,$f4
    li $v0,3 
    syscall

    li $v0,4
    la $a0,salto
    syscall

    li $v0,4
    la $a0,menor
    syscall

    mov.d $f12,$f2
    li $v0,3
    syscall
less:
    mov.d $f2,$f6 
    j next

greater:
    mov.d $f4,$f6 
    j next
end:
    li $v0,10 
    syscall