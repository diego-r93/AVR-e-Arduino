;
; Exe_5.8_g.asm
;
; Created: 12/08/2020 08:27:09
; Author : diego
;


; Replace with your application code

.org 0x000

INICIO:
	ldi R16,0xFF
	out DDRD,R16
	sts UCSR0B,R1
	ldi R20,0xFF
			
PRINCIPAL:	
	mov R21, R20
	com R21
	out PORTD, R21
	dec R20
	rcall ATRASO		
	rjmp  PRINCIPAL
	
ATRASO:
	ldi R19,20
VOLTA:
	dec  R17                                      
	brne VOLTA
	inc  R18
	brne VOLTA
	dec  R19
	brne VOLTA
	ret