  ORG 0000h
  LJMP BEGIN	;LJMP jumps to the next 16bit address
  ORG 000bh
  LJMP ISR
BEGIN:	
  MOV TMOD,#01H							; Start the timer in Continuous mode
  MOV IE,#82H							; Enable interrupts
  MOV R0,#0AH							; Initial load value for 10 loops.
  MOV TH0,#73H							; Intiial timer values for 39ms
  MOV TL0,#97H		
  MOV TCON,#10H							; start the timer
ENDLOOP:
  SJMP ENDLOOP							; Main loop
ISR:
  MOV A,R0								; HAndle the ISR on every timer overflow.
  SUBB A,#01H
  MOV R0,A
  JZ LOGIC								
  MOV TH0,#73H
  MOV TL0,#97H
  MOV TCON,#10H
  RETI
LOGIC:									
  CPL P1.0								; Ensure that logic is handled on every R0 going to 0 and then restarting the timer system.
  MOV R0,#0AH
  MOV TH0,#73H
  MOV TL0,#97H
  MOV TCON,#10H
  RETI
