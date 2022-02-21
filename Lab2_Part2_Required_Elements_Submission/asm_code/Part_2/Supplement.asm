  ORG 0000h
  LJMP BEGIN	;LJMP jumps to the next 16bit address
  ORG 000bh
  LJMP ISR
BEGIN:	
  MOV R1,#00H								; INitialize a register R1 to 00H to rollover until 7FH
  MOV R2,#80H								; INitialize a register R2 to 80H to rollover until FFH
  MOV TMOD,#01H								; Timer initialization module.
  MOV IE,#82H
  MOV R0,#0AH
  MOV TH0,#73H
  MOV TL0,#97H
  MOV TCON,#10H
  SJMP ENDLOOP
ENDLOOP:
  MOV DPTR,#500H							; Set a random address and feed in values on every call to this label.
  MOV A,R1
  MOVX @DPTR,A
  INC R1
  CJNE R1,#80H,ENDLOOP
  MOV R1,#00H
  SJMP ENDLOOP
ISR:										
  MOV DPTR,#600H							; Set a random address and feed in values on every call to the ISR
  MOV A,R2
  MOVX @DPTR,A
  INC R2
  CJNE R2,#00H,I
  MOV R2,#80H
I:  
  MOV A,R0									
  SUBB A,#01H
  MOV R0,A
  JZ LOGIC
  MOV TH0,#73H
  MOV TL0,#97H
  MOV TCON,#10H
  RETI
LOGIC:										
  CPL P1.0									; Ensure that logic is handled on every R0 going to 0 and then restarting the timer system.
  MOV R0,#0AH
  MOV TH0,#73H
  MOV TL0,#97H
  MOV TCON,#10H
  RETI