;Se va a simular una máquina expendedora de café. Al usar la interrupción 0, que muestre el
;precio seleccionado en la línea1 del display LCD, por ejemplo: 2 soles. Y al usar la interrupción 1
;muestra:
;En la Línea1: Preparando....
;En la Línea2: Muestra una barra de progreso animado que va avanzado. De tal manera que al finalizar
;la barra de progreso muestre:
;Línea 1: LISTO!! y en la Línea 2: recoja su cafe
;Para la barra de progreso debe crear un nuevo carácter de la forma de una caja(rectángulo) lleno por
;dentro. Indicar el UPDATE FREQ a usar.
;Update Freq. : 500
	org 0h
	sjmp main
	org 3h
	ljmp inter_ext_0
	org 13h
	ljmp inter_ext_1
main:
	lcall init
	setb IT0
	setb EX0
	setb P3.2
	setb IT1
	setb EX1
	setb P3.3
	setb EA
	lcall configura_LCD
	mov R0,#offCur
	lcall wrLCDcom4
	lcall setCGRAM4
	db 0Fh, 0Fh, 0Fh, 0Fh, 0Fh, 0Fh, 0Fh,20h	;memoria 0
	sjmp $
inter_ext_0:
	lcall fila1
	lcall prtLCD4
	db "                ",0
	lcall fila1
	lcall prtLCD4
	db "2 soles         ",0
	reti
inter_ext_1:
	lcall fila1
	lcall prtLCD4
	db "                ",0
	lcall fila1
	lcall prtLCD4
	db "Preparando....  ",0
	mov R7,#16
	lcall fila2
prtbox:
	lcall prtLCD4
	db 8,0
	lcall retardo_para_lab3
	mov A,R7
	dec A
	mov R7,A
	jnz prtbox
	lcall retardo_para_lab3
	sjmp final
final:
	lcall fila1
	lcall prtLCD4
	db "                ",0
	lcall fila2
	lcall prtLCD4
	db "                ",0
	lcall fila1
	lcall prtLCD4
	db "LISTO!!         ",0
	lcall fila2
	lcall prtLCD4
	db "Recoja su cafe  ",0
	reti
fila1:
	mov A,#1	
	mov B,#0	
	lcall placeCur4	
	ret
fila2:
	mov A,#2	
	mov B,#0	
	lcall placeCur4	
	ret
$INCLUDE(SubFrecuentes.inc)
$INCLUDE(LCDRutinas.inc)
	end