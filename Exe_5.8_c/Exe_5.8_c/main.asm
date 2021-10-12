;
; Exe_5.8_c.asm
;
; Created: 12/08/2020 07:25:19
; Author : diego
;


; Replace with your application code

.def AUX = R20
.ORG 0x000

INICIO:
	LDI R16,0xFF
	OUT DDRD,R16
	STS UCSR0B,R1

	LDI AUX,0xFF	
	OUT PORTD,AUX
	RCALL ATRASO
	LDI AUX, 0b11111110
	SEC
			
PRINCIPAL:		
	OUT PORTD,AUX
	ROL AUX
	RCALL ATRASO		
	RJMP  PRINCIPAL
	
ATRASO:
	LDI R19,10
VOLTA:
	DEC  R17                                      
	BRNE VOLTA
	DEC  R18
	BRNE VOLTA
	DEC  R19
	BRNE VOLTA
	RET
