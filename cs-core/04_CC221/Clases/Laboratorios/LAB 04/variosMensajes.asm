
	org 8000h
; poniendo datos en la RAM
	MOV 30H, #'A'
	MOV 31H, #'B'
	MOV 32H, #'C'
	mov 33H, #'D'
	mov 34H, #'E'
	MOV 35H, #0		; caracter de indicación de fin de envio
	lcall inicioLCD
    	
;=====================================================
; Comienza el envio de datos
	MOV R1, #30H		; datos a enviar ya han sido almacenados en la RAM 
				; del 8051, dirección de inicio 30H
loop:
	mov A, @R1		; 
	jz finish		; si A es 0, entonces termina salta a "finish"
	mov R0,A
	lcall wrLCDdata4	; envia datos en el registro "A" al módulo LCD
	inc R1			; 
	jmp loop		; repite
finish:
	mov R0,#offCur
	lcall wrLCDcom4
	lcall waitkey
	mov R0,#clrDsp		; limpia el display
	lcall wrLCDcom4
	mov A,#2
	lcall delay
	; ----------------------------------------------------
	; localiza el cursor sobre la línea 1, posición 3 y imprime un mensaje
    	mov   a, #1        ; fila 1
    	mov   b, #0        ; posición 0
    	lcall placeCur4
    	lcall prtLCD4      ; muestra mensaje
    	db "Arquitectura de"
    	db 0
    	mov A,#200
    	lcall delay
    	mov   a, #2        ; fila 2
    	mov   b, #4        ; posición 4
    	lcall placeCur4
    	lcall prtLCD4      ; muestra mensaje
    	db "Computadores"
    	db 0
	ljmp 2F0h	;Retorna al monitor
	
$INCLUDE(subrutinasDeUsoFreq.inc)
$INCLUDE(subrutinas_LCD_P1.inc)                                                                                                                
    end
