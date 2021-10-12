;
; Exe_5.8_f.asm
;
; Created: 12/08/2020 08:10:49
; Author : diego
;


; Replace with your application code

.org 0x000

INICIO:
	ldi R16,0xFF
	out DDRD,R16
	sts UCSR0B,R1
	ldi R20,0x00
			
PRINCIPAL:	
	mov R21, R20
	com R21	
	out PORTD, R21
	inc R20
	rcall ATRASO		
	rjmp  PRINCIPAL
	
ATRASO:
	ldi R19,20
VOLTA:
	dec  R17                                      
	brne VOLTA
	dec  R18
	brne VOLTA
	dec  R19
	brne VOLTA
	ret