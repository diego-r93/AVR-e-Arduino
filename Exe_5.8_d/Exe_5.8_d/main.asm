;
; Exe_5.8_d.asm
;
; Created: 12/08/2020 08:01:07
; Author : diego
;


; Replace with your application code

.def AUX = R20
.org 0x000

INICIO:
	ldi R16,0xFF
	out DDRD,R16
	sts UCSR0B,R1

	ldi AUX,0xFF	
	out PORTD,AUX
	rcall ATRASO
	ldi AUX, 0b01111111
	sec
			
PRINCIPAL:		
	out PORTD,AUX
	ror AUX
	rcall ATRASO		
	rjmp  PRINCIPAL
	
ATRASO:
	ldi R19,10
VOLTA:
	dec  R17                                      
	brne VOLTA
	dec  R18
	brne VOLTA
	dec  R19
	brne VOLTA
	ret
