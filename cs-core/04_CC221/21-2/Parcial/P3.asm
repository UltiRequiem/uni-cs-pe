;Desarrolle un programa que calcule el décimo y el doceavo término de la serie de
;Fibonacci(1,1,2,3,5,8,13,21,34,*55*,89,*144*). Enviar ambos resultados calculados
;en el programa al display LCD.
;Indicar el UPDATE FREQ a usar.
;Update Freq. : 2000
	org 0h
main:
	lcall init
	lcall configura_LCD
	mov R0,#offCur
	lcall wrLCDcom4
	mov R5,#1	;hace de a
	mov R6,#1	;hace de b
	mov R0,#0	;hace de c
	mov R2,#10
	mov R1,#2
repite:
	mov A,R5
	add A,R6
	mov R0,A
	inc R1
	cjne R1,#10,continue1
	lcall wrLCDdata4
continue1:
	cjne R1,#12,continue2
	lcall fila2
	lcall wrLCDdata4
continue2:
	mov A,R6
	mov R5,A
	mov A,R0
	mov R6,A
	djnz R2,repite
	sjmp $
fila2:
	mov A,#2	
	mov B,#0	
	lcall placeCur4	
	ret
$INCLUDE(SubFrecuentes.inc)
$INCLUDE(LCDRutinas.inc)
	end