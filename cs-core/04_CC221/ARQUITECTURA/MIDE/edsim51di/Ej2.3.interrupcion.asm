;encender LED 
	ORG 0H
	
	MOV A, #11111110B
	CALL LEDS
	
	LEDS:
		MOV P1,A
		RL A
	CALL LEDS
	END