init:
	mov PCON,#80H
	mov TMOD,#20H
	mov TCON,#41H
	mov TH1,#0FDH
	mov SCON,#50H
	ret
print: 
	pop dph ;coloca dirección de reterno en dptr
	pop dpl
prtstr:
	clr A
	movc A,@A+DPTR
	cjne A,#0h,mchrok
	sjmp prtdone
mchrok:
	lcall sndchr
	inc DPTR
	sjmp PRTSTR
prtdone:
	mov A,#1h
	jmp @A+DPTR
prthex:
	lcall binasc
	lcall sndchr
	mov A,R2
	lcall sndchr
	ret
sndchr:
	clr TI
	mov SBUF,A
txloop:
	jnb TI,txloop
	ret
;Se le pasa un numero hexadecimal de dos digitos
;y nos devuelve dos codigos ascii del digito mas 
;significativo en el registro A y del digito menos
;significativo en el registro R2
binasc:
	mov R2,A ;se mueve a R2 para salvar el valor de A
	anl A,#0Fh ;se convierte el dígito menos significativo
	add A,#0F6h ;lo ajusta
	jnc noadj1
	add A,#07h
noadj1:
	add A,#3Ah ;lo hace ascii
	xch A,R2 ;pone el resultado en R2
	swap A ;se convierte ahora el digito más significativo
	anl A,#0Fh
	add A,#0F6h ;lo ajusta
	jnc noadj2
	add A,#07h
noadj2:
	add A,#3Ah ;lo hace ascii
	ret
display:
	inc a ;incremento el valor de A
	movc a,@a+pc ;muevo a A el valor del contenido de la dirección de memoria (pc+a)
	ret ;Retorno de la subrutina al programa principal
	db 0C0h ;Con este código se muestra "0" en el display
	db 0F9h ;Con este código se muestra "1" en el display
	db 0A4h ;"2"
	db 0B0h ;"3"
	db 99h ;"4"
	db 92h ;"5"
	db 82h ;"6"
	db 0F8h ;"7"
	db 80h ;"8"
	db 90h ;"9"
	db 88h ; a
	db 83h ; b
	db 0c6h ; c
	db 0a1h ; d
	db 86h ; e
	db 8eh ; f
;Sirve para convertir a decimal
;un número hexadecimal y para
;enviar al terminal tres digitos decimales
;se usan 31h, 32h y 33h
envio_tres_digitos:
	mov B,#100
	div AB
	mov 31h,A
	mov A,B
	mov B,#10
	div AB
	mov 32h,A
	mov 33h,B
	mov A,31h
	add A,#30h
	lcall sndchr
	mov A,32h
	add A,#30h
	lcall sndchr
	mov A,33h
	add A,#30h
	lcall sndchr
	ret
envio_un_digito:
	add A,#30h
	lcall sndchr
	ret
;Sirve para convertir a decimal
;un número hexadecimal y para
;enviar al terminal dos digitos decimales
;se usan 32h y 33h
envio_dos_digitos:
	mov B,#10
	div AB
	mov 32h,A
	mov 33h,B
	mov A,32h
	add A,#30h
	lcall sndchr
	mov A,33h
	add A,#30h
	lcall sndchr
	ret
getbyt:
	lcall getchr ; consigue el caracter ascii msb
	lcall ascbin ; lo convierte a binario
	swap A ; lo mueve a la mitad mas significativa del acumulador
	mov B, A ; lo salva en B
	lcall getchr ; consigue el caracter ascii lsb
	lcall ascbin ; lo convierte a binario
	orl A, B ; combina las dos mitades
	ret
getchr: 
	jnb ri, getchr ; espera hasta que el caracter sea recibido
	mov a, sbuf ; consigue el caracter
	anl a, #7fh ; mask off 8th bit
	clr ri ; limpia el bit de estado serial
	ret
ascbin:
	add a, #0d0h ; si chr < 30 entonces error
	jnc notnum
	clr c ; chequea si chr es 0-9
	add a, #0f6h ; lo ajusta
	jc hextry ; salta si chr no es 0-9
	add a, #0ah ; si lo es entonces lo ajusta
	ret
hextry:
	clr acc.5 ;
	clr c ; chequea si chr es a-f
	add a, #0f9h ; lo ajusta
	jnc notnum ; si no es a-f entonces error
	clr c ; averigua si char es 46 o menos.
	add a, #0fah ; ajusta el acumulador
	jc notnum ; si carry=1 entonces no es un número hex
	anl a, #0fh ; limpia bits no usados
	ret
notnum:
;setb errorf ;
	ret
retardo_para_lab3:
	mov R4,#8
loop:
	mov R1,#250
	djnz R1,$
	djnz R4,loop
	ret
delay:

dec a ; 1
d_olp:
push acc ; 2 \
mov a, #0a6h ; 1 |
; |
d_ilp: inc a ; 1 \ |
nop ; 1 | |
nop ; 1 | |
nop ; 1 | |
nop ; 1 | |
nop ; 1 |- 11 | (acc-1)
nop ; 1 | cycles |- msec
nop ; 1 | |
nop ; 1 | |
jnz d_ilp ; 2 / |
; |
nop ; 1 |
nop ; 1 |
nop ; 1 |
pop acc ; 2 |
; |
djnz acc,d_olp ; 2 /

; necesita esperar 998 microsegundos más

mov a, #0a6h ; 1

d_lp2: inc a ; 1 \
nop ; 1 |
nop ; 1 |
nop ; 1 |
nop ; 1 |
nop ; 1 |- 11
nop ; 1 | cycles
nop ; 1 |
nop ; 1 |
jnz d_lp2 ; 2 /
nop ; 1
nop ; 1
nop ; 1
nop ; 1
nop ; 1

ret ; 2
; ====================================================
;=====================================================
;Devuelve tres codigos ASCII de tres digitos decimales
;En las posiciones de memoria 30h,31h y 32h
;=====================================================
tres_digitos_decimales:
	mov B,#100
	div AB
	add A,#30h
	mov 30h,A
	mov A,B
	mov B,#10
	div AB
	add A,#30h
	mov 31h,A
	mov A,B
	add A,#30h
	mov 32h,A
	ret
;=====================================================
;Devuelve dos codigos ASCII de dos digitos decimales 30h,31h
;=====================================================
dos_digitos_decimales:
	mov B,#10
	div AB
	add A,#30h
	mov 30h,A
	mov A,B
	add A,#30h
	mov 31h,A
	ret
;===============================================================
; waitKey es una rutina util que imprime el mensaje
; "presione una tecla para continuar" y luego espera hasta que
; un caracter sea recibido.
;===============================================================
waitKey:
lcall print
db "presione una tecla para continuar"
db 0
lcall crlf
lcall getchr ; espera hasta que se presione una tecla
ret
;===============================================================
; subrutina crlf
; crlf envia un carriage return y line feed fuera del puerto serie
;===============================================================
crlf:
mov a, #0Dh ; print cr
lcall sndchr
cret:
mov a, #0Ah ; print lf
lcall sndchr
ret
;===============================================================
