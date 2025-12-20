; constantes
LCD_DATA equ 090h ; puerto 1 es usado para datos o instrucciones
LCD_DB4 equ 094h ; high nibble del puerto 1(P1.4) es usado para datos o instrucciones
LCD_DB5 equ 095h ; high nibble del puerto 1(P1.5) es usado para datos o instrucciones
LCD_DB6 equ 096h ; high nibble del puerto 1(P1.6) es usado para datos o instrucciones
LCD_DB7 equ 097h ; high nibble del puerto 1(P1.7) es usado para datos o instrucciones
LCD_RS equ 093h ; p1.3 LCD linea Register Select
LCD_RW equ 091h ; p1.1 LCD linea Read / Write
LCD_E equ 092h ; p1.2 LCD linea Enable

;instrucciones del sistema
Config equ 28h ; Uso de 4 bits de datos, 2 lineas, tamaño de font 5 x 7 seleccionado.
entryMode equ 6 ; incrementar cursor, no traslada display, incremento automático del registro AC al escribir.

;instrucciones de control del cursor
offCur equ 0Ch ;desaparece al cursor
lineCur equ 0Eh;cursor se muestra como una línea
blinkCur equ 0Dh;cursor parpadeante
combnCur equ 0Fh;enciende el display, enciende cursor y parpadea el caracter en la posición del cursor
homeCur equ 02h ;se coloca el cursor al principio de la línea, a la izquierda.
shLfCur equ 10h;desplaza al cursor a la izquierda
shRtCur equ 14h;Desplaza al cursor a la derecha

;instrucciones de control del display
clrDsp equ 01h ;Limpia el display así como el contenido de la memoria
offDsp equ 0Ah ;blanquea el display(display se apaga)no hay efecto de parpadeo y el cursor es visualizado
onDsp equ 0Eh ;Muestra mensaje en el display(el display hace aparecer los caracteres)
shLfDsp equ 18h ;Desplazamiento del display a la izquierda
shRtDsp equ 1Ch ;Desplazamiento del display a la derecha
		
; ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; subrutinas
; ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
;Subrutina de configuración del LCD
configura_LCD:
	lcall resetLCD4
	lcall initLCD4
	ret 
;================================================
;Subrutina que se llama al inicio de su programa
;Para habilitar el LCD
;================================================
resetLCD4:
	CLR LCD_RS ; clear RS - indica que instrucciones estan siendo enviados al módulo
	CLR P1.7 ; se fijan los bits para...
	CLR P1.6 ;... power-on-reset
	SETB P1.5 ; 
	CLR P1.4 ;
	SETB LCD_E ; inicia pulso Enable
	CLR LCD_E ; termina el pulso Enable
	lcall retardo;
	SETB LCD_E ; inicia pulso Enable
	CLR LCD_E ; termina el pulso Enable
	SETB P1.7 ;
	SETB LCD_E ;inicia pulso Enable
	CLR LCD_E ;termina el pulso Enable
	lcall retardo ;
	ret

; ====================================================
; subrutina initLCD4 - inicializa el LCD
; ----------------------------------------------------
initLCD4:
	clr LCD_RS ; LCD linea de Register Select
	clr LCD_RW ; linea de Read / Write
	clr LCD_E ; linea de Enable
	mov r0, #entryMode ; fijar Entry Mode
	acall wrLCDcom4 ; incrementar cursor a la derecha, no traslada el display
	mov r0, #onDsp ; Enciende el display, home cursor
	lcall wrLCDcom4
	ret	

;=================================
;Subrutina de retardo de tiempo
;=================================
retardo:
	mov R0,#50
	djnz R0,$
	ret
;==================================
;Subrutina de retardo de mayor tiempo
;==================================
retardo2:
	mov R5,#5
vuelve:
  	mov R3,#100
  	djnz R3,$
  	djnz R5,vuelve
  	ret

; ==========================================================
; subrutina crShLf4
; Esta rutina traslada el cursor a la izquierda. El numero de
; posiciones a ser trasladado es localizado en el acumulador.
; entrada : acumulador indica numero de posiciones a trasladar
; salida : nada
; ==========================================================
;
crShLf4:
	jz ret_scl
	mov r0, #shLfCur ; palabra de control para trasladar a la izquierda
	acall wrLCDcom4
	dec acc
	sjmp crShLf4
ret_scl: 
	ret
; ==========================================================
; subrutina crShRt4
; Esta rutina traslada el cursor a la derecha. El numero de
; posiciones a ser trasladado es localizado en el acumulador.
; entrada : acumulador indica el numero de posiciones a trasladar
; salida : nada
; ==========================================================
;
crShRt4:
	jz ret_scr
	mov r0, #shRtCur ; palabra de control para trasladar a la derecha
	acall wrLCDcom4
	dec acc
	sjmp crShRt4
	ret_scr: ret
; ==========================================================
; subrutina placeCur4
; Esta rutina fija la posicion del cursor. La posicion del cursor
; es localizado en el registro b. La posicion del cursor empieza
; en 0. El acumulador da el numero de linea.
; entrada: acumulador indica el numero de linea (1, 2)
; : el registro b guarda la posicion del cursor
; salida : nada
; ==========================================================
;
placeCur4:
	dec acc ; acc=0 para linea=1
	jnz line2 ; si acc=0 luego primera lnea
	mov a, b
	add a, #080h ; palabra de control para la linea 1
	sjmp setcur
line2:
	mov a, b
	add a, #0C0h ; palabra de control para la l¡nea 2
setcur:
	mov r0, a ; localizar palabra de control
	acall wrLCDcom4 ;
	ret
; ==========================================================
; subrutina setCGRAM4
; Esta rutina fija la direccion del Character Generator RAM. El
; caracter [0..7] es localizado en el acumulador. La fila del font
; es localizado en el registro b. Las instrucciones 40h a 7Fh
; selecciona las direcciones del CGRAM 0 to 3Fh (0 to 63 decimal).
; El font de 5x7 para el caracter es asumido. Esto es, cada posici¢n del
; caracter contiene una matriz de 40 puntos arreglados en 8 filas de
; 5 puntos cada uno. Las 7 filas son para los caracteres y la 8va
; fila para el cursor debajo del caracter. Direcciones de CGRAM "0" corresponde
; a la primera fila del caracter 0, direccion "7" corresponde
; al 8vo (ultima) fila del caracter 0, y direccion 3Fh
; corresponde a la 8va fila del caracter 7.
;
; entrada : acumulador indica el código del caracter [0..7]
; el registro b guarda la fila del font [0..7]
; salida : nada
; ==========================================================
;
setCGRAM4:
		push b
		mov b, #8
		mul ab ; multiplica numero del caracter por 8
		pop b ; b sostiene numero de fila
		add a, b ; en a se sostiene CGRAM address
		add a, #40h ; convert to instruction
		mov r0, a ; place instruction
		acall wrLCDcom4 ; issue command
		ret
; ==========================================================
; subrutina dspShLf4
; Esta rutina traslada los contenidos del LCD a la izquierda. El
; numero de caracteres a ser trasladados es localizado en el
; acumulador.
; entrada : acumulador indica el numero de caracteres a trasladar
; salida : nada
; ==========================================================
;
dspShLf4:
	jz ret_sdl
	mov r0, #shLfDsp ; palabra de control para trasladar a la izquierda
	acall wrLCDcom4
	dec a
	sjmp dspShLf4
ret_sdl: ret
; ==========================================================
; subrutina dspShRt4
; Esta rutina traslada los contenidos del LCD a la derecha. El
; numero de caracteres a ser trasladados es localizado en el
; acumulador.
; entrada : acumulador indica el numero de caracteres a trasladar
; salida : nada
; ==========================================================
;
dspShRt4:
	jz ret_sdr
	mov r0, #shRtDsp ; palabra de control para trasladar a la derecha
	acall wrLCDcom4
	dec a
	sjmp dspShRt4
ret_sdr: ret
; ====================================================
; subrutina wrLCDdata4
; escribe un dato al LCD
; el dato debe ser localizado en r0 para llamar el programa
; ----------------------------------------------------
wrLCDdata4:
clr LCD_E
setb LCD_RS ; selecciona enviar Dato
clr LCD_RW ; selecciona operacion de escritura
push acc ; salva acumulador
mov a, r0 ; pone byte de datos en el acc
mov c, acc.4 ; carga high nibble sobre el bus de datos
mov LCD_DB4, c ; un bit a la vez...
mov c, acc.5 ;
mov LCD_DB5, c
mov c, acc.6
mov LCD_DB6, c
mov c, acc.7
mov LCD_DB7, c
setb LCD_E ; pone a uno el pin Enable
clr LCD_E ; pone a cero el pin Enable
mov c, acc.0 ; similarmente, carga el low nibble
mov LCD_DB4, c
mov c, acc.1
mov LCD_DB5, c
mov c, acc.2
mov LCD_DB6, c
mov c, acc.3
mov LCD_DB7, c
setb LCD_E ; pone a uno el pin Enable
clr LCD_E ; pone a cero el pin Enable
lcall retardo
pop acc
ret
; ====================================================
; subrutina wrLCDcom4
; escribe una palabra de comando al LCD
; comando debe estar localizado en r0 para llamar el programa
; ----------------------------------------------------
wrLCDcom4:
clr LCD_E
clr LCD_RS ; selecciona enviar comando
clr LCD_RW ; selecciona operaci¢n de escritura
push acc ; salva el acumulador
mov a, r0 ; pone el byte de datos en el acc
mov c, acc.4 ; carga el high nibble en el bus de datos
mov LCD_DB4, c ; un bit a la vez usando...
mov c, acc.5 ; operaciones de mover bit
mov LCD_DB5, c
mov c, acc.6
mov LCD_DB6, c
mov c, acc.7
mov LCD_DB7, c
setb LCD_E ; pulsa la l¡nea Enable
clr LCD_E
mov c, acc.0 ; similarmente, carga el low nibble
mov LCD_DB4, c
mov c, acc.1
mov LCD_DB5, c
mov c, acc.2
mov LCD_DB6, c
mov c, acc.3
mov LCD_DB7, c
setb LCD_E ; pulsa la l¡nea Enable
clr LCD_E
lcall retardo
pop acc
ret

; ==========================================================
; subrutina prtLCD4
; Toma la cadena inmediatamente que sigue a la llamada a esta
; subrutina y lo displaya sobre el LCD. La cadena es leida con la
; instrucci¢n mov a, @a+dptr
; de este modo, la cadena esta en la memoria de datos.
;
; entrada : nada
; salida : nada
; destruye : acc, dptr
; ==========================================================
;
prtLCD4:
pop dph ; regresa direcci¢n de retorno en dptr
pop dpl
prtNext:
clr a ; set offset = 0
movc a, @a+dptr ; consigue chr de la memoria de c¢digo
cjne a, #0, chrOK ; si chr = 0 entonces retorna
sjmp retPrtLCD
chrOK:
mov r0, a
acall wrLCDdata4 ; enviar caracter
inc dptr ; apuntar al siguiente caracter
ajmp prtNext ; lazo hasta que finalize la cadena
retPrtLCD:
mov a, #1h ; apunta a la instrucci¢n despu‚s de la cadena
jmp @a+dptr ; retorno con una instrucci¢n de salto
; ====================================================
; subrutina sdelay - retardo de un segundo
; entrada : nada
; salida : nada
; destruye : nada - usa a
; ----------------------------------------------------
; 100h-91h=6fh=(111)decimal
; 9008 * 111 = 999888
; mas 102 del segundo lazo
; mas 8 da 999998 microsegundos
;
; microsegundos (ciclos)
; -----------------------
sdelay: push acc ; 2.17
mov a, #91h ; 1.085
sd_olp: inc a ; \
acall mdelay ; |
acall mdelay ; |
acall mdelay ; |
acall mdelay ; |
acall mdelay ; |
acall mdelay ; |
acall mdelay ; |- el lazo toma 9008 microsegundos
acall mdelay ; |
acall mdelay ; |
nop ; |
nop ; |
nop ; |
nop ; |
nop ; |
jnz sd_olp ; /
mov a, #33h ; 1.085
sd_ilp: djnz acc, sd_ilp ; -el lazo toma 2*33h=66h=(102)dec
pop acc ; 2.17
ret ; 2.17
; ====================================================
; subrutina mdelay - retardo de 1 milisegundo
; retardo para 998 microsegundos - 2 microsegundos son
; reservados para la llamada a esta rutina.
; intrada : nada
; salida : nada
; destruye : nada - usa a
; ----------------------------------------------------
; 100h-a6h=5ah=(90)decimal
; 90 * 11 = 990
; mas 8 da 998 microsegundos
;
; microsegundos (ciclos)
; -----------------------
mdelay: push acc ; 2
mov a, #0a6h ; 1
md_olp: inc a ; 1 \
nop ; 1 |
nop ; 1 |
nop ; 1 |
nop ; 1 |
nop ; 1 |- 11 ciclos
nop ; 1 |
nop ; 1 |
nop ; 1 |
jnz md_olp ; 2 /
nop ; 1
pop acc ; 2
ret ; 2


;==========================================================
;Subrutina segs0_a_9 de display LCD para cuenta en segundos
;Visualizacion de Segundos desde 0 a 9.
;==========================================================
segs0_a_9:
	mov r0,#30h
	lcall wrLCDdata4
	mov r0,#shlfcur
	lcall wrlcdcom4
	mov r0,#offcur ;no se ve el cursor
	lcall wrlcdcom4
	lcall sdelay
	mov r0,#31h
	lcall wrLCDdata4
	mov r0,#shlfcur
	lcall wrlcdcom4
	mov r0,#offcur ;no se ve el cursor
	lcall wrlcdcom4
	lcall sdelay
	mov r0,#32h
	lcall wrLCDdata4
	mov r0,#shlfcur
	lcall wrlcdcom4
	mov r0,#offcur ;no se ve el cursor
	lcall wrlcdcom4
	lcall sdelay
	mov r0,#33h
	lcall wrLCDdata4
	mov r0,#shlfcur
	lcall wrlcdcom4
	mov r0,#offcur ;no se ve el cursor
	lcall wrlcdcom4
	lcall sdelay
	mov r0,#34h
	lcall wrLCDdata4
	mov r0,#shlfcur
	lcall wrlcdcom4
	mov r0,#offcur ;no se ve el cursor
	lcall wrlcdcom4
	lcall sdelay
	mov r0,#35h
	lcall wrLCDdata4
	mov r0,#shlfcur
	lcall wrlcdcom4
	mov r0,#offcur ;no se ve el cursor
	lcall wrlcdcom4
	lcall sdelay
	mov r0,#36h
	lcall wrLCDdata4
	mov r0,#shlfcur
	lcall wrlcdcom4
	mov r0,#offcur ;no se ve el cursor
	lcall wrlcdcom4
	lcall sdelay
	mov r0,#37h
	lcall wrLCDdata4
	mov r0,#shlfcur
	lcall wrlcdcom4
	mov r0,#offcur ;no se ve el cursor
	lcall wrlcdcom4
	lcall sdelay
	mov r0,#38h
	lcall wrLCDdata4
	mov r0,#shlfcur
	lcall wrlcdcom4
	mov r0,#offcur ;no se ve el cursor
	lcall wrlcdcom4
	lcall sdelay
	mov r0,#39h
	lcall wrLCDdata4
	;mov r0,#shlfcur
	;lcall wrlcdcom4
	mov r0,#offcur ;no se ve el cursor
	lcall wrlcdcom4
	lcall sdelay
	ret
