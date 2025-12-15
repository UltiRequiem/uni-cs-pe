;Si quiero utilizar el interrupción generado por le timer 0 en modo 0
;debo de escribir las siquientes instrucciones:
	ORG 0000h        ; Vector de reset
    LJMP MAIN

ORG 000Bh        ; Vector de interrupción Timer 0
    CPL P1.0     ; Cambia el estado de P1.0 (tren de pulsos)
    RETI         ; Retorna de la interrupción

ORG 0030h        ; Inicio del programa principal
MAIN:
    MOV TMOD, #02h   ; Timer 0 en modo 2 (8-bit auto-reload)
    MOV TH0, #206    ; Valor inicial para 10kHz aprox
    SETB TR0         ; Activa Timer 0
    SETB ET0         ; Habilita interrupción Timer 0
    SETB EA          ; Habilita interrupciones globales

BUCLE:
    SJMP BUCLE       ; Bucle infinito esperando interrupciones

END
