;Ejemplo1 Generar un tren de pulsos de 10khz sobre 
;el pin P1.0 usando interrupciones del timer 0

org 0000h ;vector de rest
sjmp main
org 00Bh ;vector interrupción del timer 0
cpl P1.0
reti 
	org 0030h ;programa principal
main:
	mov TMOD,#2 ;Timer 0 en modo 2
	mov TH0,#206 ;cargar 206 en TH0
	setb TR0 ;inicia el timer 0
	setb ET0 ;habilita interrución del timer 0
	setb EA ;habilita interrución global
	sjmp $ ;se queda aquí dando vueltas esperando la interrupción
	END