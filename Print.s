; Print.s
; Student names: Genki Oji and David Yu
; Last modification date: 3/28/16
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 

    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString

    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix
	PRESERVE8
		
num		EQU	0
div		EQU	4
cnt		EQU 8
link	EQU	8

    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB

  

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec
	PUSH {R4, LR}
	
	SUB	SP, #12
	MOV	R4, SP
	STR	R0, [R4, #num]
	MOV	R0, #0
	STR	R0, [R4, #cnt]
	MOV	R0, #10
	STR	R0, [R4, #div]
	
	LDR	R0, [R4, #num]
	LDR	R2, [R4, #div]
	
	;LDR	R4, SP
loop					;this loop is to store least significant numbers first onto stack
	LDR	R12,[R4,#cnt]
	UDIV	R3, R0, R2
	MUL	R1, R3, R2
	SUB	R1, R0, R1		;R1 is least significant number
	PUSH {R1}			;push LSB to MSB
	ADD	R12, #1			;cnt++
	STR	R12, [R4, #cnt]	
	MOVS	R0, R3		
	BNE	loop
	LDR	R12, [R4, #cnt]
OUT_DEC					;this loop is to output the most significant numbers first
	POP {R0}
	ADD	R0, R0, #0x30	;turn number into ascii
	BL	ST7735_OutChar
	SUBS	R12, #1
	BNE	OUT_DEC
	ADD	SP, #12		;Deallocate
	POP {R4, LR}
	BX  LR
;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 "
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutFix
	SUB	SP, #8
	STR	R0, [SP, #num]
	MOV	R3, #1000
	STR	R3, [SP, #div]
	MOV	R12, #10
	STR	LR, [SP, #link]
;if R0 > 9999, output *.***
	MOV	R1, #9999
	CMP	R0, R1
	BLS	Valid_Num
	MOV	R0, #0x2A			;*
	BL	ST7735_OutChar
	MOV	R0,	#0x2E			;.
	BL	ST7735_OutChar
	MOV	R0, #0x2A			;*
	BL	ST7735_OutChar
	MOV	R0, #0x2A			;*
	BL	ST7735_OutChar
	MOV	R0, #0x2A			;*
	BL	ST7735_OutChar
	B	done
;else turn number into floating point number
Valid_Num
	LDR	R1, [SP,#num]
	LDR	R3, [SP, #div]
	UDIV	R0, R1, R3
	ADD	R0, #0x30			;convert to ASCII value
	BL	ST7735_OutChar
	MOV	R0,	#0x2E				;.
	BL	ST7735_OutChar
OUT_FIX
	LDR	R1, [SP, #num]
	LDR	R3, [SP, #div]
	UDIV	R0, R1, R3
	MUL	R2, R0, R3
	SUB	R1, R1, R2		;R1 contains remainder
	STR	R1, [SP, #num]	;This line isn't very necessary
	UDIV	R3, R12
	STR	R3, [SP, #div]	
	UDIV	R0, R1, R3
	ADD	R0, #0x30
	BL	ST7735_OutChar
	LDR	R3, [SP, #div]
	CMP	R3, #1
	BHI	OUT_FIX
done
	LDR	LR, [SP, #link]
	ADD	SP, #8		;deallocate
    BX   LR
 
     ALIGN
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
