ORG 8000H

;--------------------------------------
; Variables
caritaOK      EQU  0
caritaFail    EQU  1
cuenta        DATA 30H  ; contador principal (0 a 39)
timerCont     DATA 31H  ; contador software para 17ms
banderaFin    DATA 32H  ; bandera para saber si completó (0=incompleto, 1=fin)
;--------------------------------------

; Configurar LCD y mostrar mensaje inicial
LCALL inicioLCD
LCALL setCGRAM4
MOV A,#caritaOK
MOV B,#0
LCALL prtLCD4
DB 20H,0AH,20H,1FH,11H,0EH,20H,20H  ; Carita feliz
DB 11H,0AH,11H,04H,20H,0EH,11H,20H  ; Carita molesta

; Configurar Interrupciones
SETB IT0             ; INT0 por flanco de bajada
MOV DPTR, #ISR0
LCALL setintvec
SETB EX0             ; habilita INT0
SETB EA              ; habilita global

; Configurar INT del Timer0 en modo 2
MOV TMOD, #02H       ; Timer0 modo 2 (8 bits auto-reload)
MOV TH0, #0B0H       ; TH0 = 0xB0 (~1ms por interrupción)
MOV TL0, #0B0H
SETB ET0             ; Habilita interrupciones del Timer0
SETB TR0             ; Inicia Timer0

; Inicializar contadores
CLR A
MOV cuenta, A
MOV timerCont, A
CLR banderaFin

; Bucle principal espera finalización o interrupción
ESPERA:
JB banderaFin, MOSTRAR_FELIZ
SJMP ESPERA

MOSTRAR_FELIZ:
LCALL carita_feliz
SJMP $

INTERRUPCION_EXTERN0:
; Rutina de interrupción externa INT0
CLR TR0          ; detener Timer
CLR ET0
CLR EX0          ; desactiva INT0
CLR EA
LCALL carita_molesta
SJMP $

;--------------------------------------
; Timer0 ISR
ORG 003BH
TIMER0_ISR:
PUSH ACC
PUSH PSW

INC timerCont
MOV A, timerCont
CJNE A, #17, SALIR_ISR

; Cada 17ms ? actualizar display
CLR timerCont
MOV A, cuenta
CJNE A, #40, CONTAR
; Llego a 40
SETB banderaFin
CLR TR0
CLR ET0
CLR EX0
CLR EA
SJMP SALIR_ISR

CONTAR:
; Mostrar número actual en LCD
MOV B, #0
LCALL placeCur4
MOV A, cuenta
LCALL bin2bcd_ascii
MOV R0, #30H
LCALL wrlcddata4
MOV R0, #31H
LCALL wrlcddata4
MOV R0, #32H
LCALL wrlcddata4
INC cuenta

SALIR_ISR:
POP PSW
POP ACC
RETI

;--------------------------------------
carita_feliz:
MOV R0, #offCur
LCALL wrLCDcom4
MOV A, #1
MOV B, #7
LCALL placeCur4

PARPADEO_OK:
LCALL prtLCD4
DB 8, 0
LCALL delay
MOV R0, #offDsp
LCALL wrLCDcom4
LCALL delay
MOV R0, #onDsp
LCALL wrLCDcom4
SJMP PARPADEO_OK

carita_molesta:
MOV R0, #offCur
LCALL wrLCDcom4
MOV A, #1
MOV B, #7
LCALL placeCur4

PARPADEO_FAIL:
LCALL prtLCD4
DB 1, 0
LCALL delay
MOV R0, #offDsp
LCALL wrLCDcom4
LCALL delay
MOV R0, #onDsp
LCALL wrLCDcom4
SJMP PARPADEO_FAIL

;--------------------------------------
; Subrutinas necesarias
$INCLUDE(subrutinasDeUsoFreq.inc)
$INCLUDE(subrutinas_LCD_TMC51.inc)
END
