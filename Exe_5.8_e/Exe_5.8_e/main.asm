;
; Exe_5.8_e.asm
;
; Created: 12/08/2020 08:07:28
; Author : diego
;


; Replace with your application code

.def AUX = R20
.org 0x000

INICIO:
	ldi R16,0xFF
	out DDRD,R16
	sts UCSR0B,R1

	ldi AUX,0x00	
	out PORTD,AUX
	rcall ATRASO
	ldi AUX, 0b00000001
				
PRINCIPAL:		
	out PORTD,AUX
	rol AUX
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
