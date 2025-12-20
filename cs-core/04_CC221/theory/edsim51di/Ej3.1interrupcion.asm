;Usando prioridades en el ejemplo de 
;trenes de pulsos 
;Se tiene el programa anterior modificado: 
org 0000h 
sjmp main 
 
org 000Bh  ; vector de interrupción del timer 0 
cpl P3.4        ; genera una señal de 20 khz 
reti                ; retorna de la interrupción 
 
org 001Bh           ;vector de interrupción del timer 1 
sjmp timer1ISR  ;salta al ISR del timer 1 
 
org 0030h                   ;programa principal 
main: 
    mov TMOD,#12h  ;timer 0 en modo de 8 bits con autorecarga y timer 1 en modo 
                                   ;de 16 bits 
    mov TH0,#231      ;valor de autorecarga 
    setb TR0                ;arranca el timer 0 

    setb TF1                ;se fuerza interrupción del timer 1 
    setb ET0                ;se habilita la interrupción del timer 0 
    setb PT0               ;el timer 0 se fija a alta prioridad 
    setb ET1                ;se habilita la interrupción del timer 1 
    setb EA                  ;se habilita la interrupción global 
    sjmp $                    ;aquí está dando vueltas pero espera por interrupciones 
;Viene aquí cada vez que hay una interrupción del timer1 
timer1ISR: 
    clr TR1                   ;detiene el timer 1 
    mov TH1,#0FCh    ;inicializa el timer 1 con “FC18h” 
    mov TL1,#18h        ;(65536 – 1000= 64536)(este número es FC18h en hexadecimal) 
    setb TR1                 ;arranca el timer 1 
    cpl P3.5                  ;se genera 500 hz 
    reti                          ;retorna de la interrupción
    END