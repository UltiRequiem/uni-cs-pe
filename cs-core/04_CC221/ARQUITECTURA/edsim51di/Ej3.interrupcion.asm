;Ejemplo 2(Usando más de una interrupción): 
;Deseamos generar dos trenes de pulsos de diferentes frecuencias. Por ejemplo, 
;un tren de pulsos de 20KHz sobre P3.4 y un tren de pulsos de 500Hz sobre P3.5. 

;El programa debajo pudiera ser usado para generar estos trenes de pulsos. 
ORG 0000h           ; direccion de inicio Vector de reset
    SJMP MAIN

ORG 000Bh           ; Vector de interrupción Timer 0
    CPL P3.4        ; Invierte el estado de P3.4 (tren de 20kHz)
    RETI

ORG 001Bh           ; Vector de interrupción Timer 1
    LJMP TIMER1ISR  ; Salta a la rutina del Timer 1

ORG 0030h           ; Programa principal
MAIN:
    MOV TMOD, #12h  ; Timer 0 en modo 2 (auto-reload), Timer 1 en modo 1 (16 bits)
    
    ; Configuración para Timer 0: 20 kHz ? periodo de 50 µs
    ; Valor = 256 - (50µs / 1µs) = 256 - 50 = 206
    MOV TH0, #206   ; Auto-recarga
    MOV TL0, #206

    ; Configuración para Timer 1: 500 Hz ? periodo de 2 ms
    ; Valor = 65536 - 2000 = 63536 = F830h
    MOV TH1, #0F8h
    MOV TL1, #30h

    SETB TR0        ; Inicia Timer 0
    SETB TR1        ; Inicia Timer 1

    SETB ET0        ; Habilita interrupción Timer 0
    SETB ET1        ; Habilita interrupción Timer 1
    SETB EA         ; Habilita interrupciones globales

ESPERA:
    SJMP ESPERA     ; Bucle infinito

; Rutina de interrupción para Timer 1
TIMER1ISR:
    CPL P3.5        ; Invierte el estado de P3.5 (tren de 500Hz)
    RETI
    END
