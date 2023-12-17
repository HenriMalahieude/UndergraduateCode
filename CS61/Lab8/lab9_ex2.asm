;=================================================
; Name: Henri Malahieude
; Email: 
; 
; Lab: lab 9, ex 1
; Lab section: 
; TA: 
; 
;=================================================

; test harness
.orig x3000

LD R5, SUB_LOAD_VALUE_ADDR
JSRR R5

LD R5, SUB_PRINT_DECIMAL_ADDR
JSRR R5

ST R0, SAVE_CHAR

LEA R0, OPEN_STR
PUTS

LD R0, SAVE_CHAR
OUT

LEA R0, END_STR
PUTS

LD R3, AsciiOffset
AND R0, R0, #0
ADD R0, R4, R3
OUT

halt
;-----------------------------------------------------------------------------------------------
; test harness local data:

SUB_LOAD_VALUE_ADDR .FILL x3200
SUB_PRINT_DECIMAL_ADDR .FILL x3400

SAVE_CHAR .BLKW #1
OPEN_STR .STRINGZ "The number of 1's in '"
END_STR .STRINGZ "' is: "
AsciiOffset .FILL x30


;===============================================================================================
.end

; subroutines:

;------------------------------------------------------------------------------------------
; Subroutine: SUB_LOAD_VALUE (Be sure to fill details in below)
;
; Parameter (R): none
; Return Value: R1
;------------------------------------------------------------------------------------------
.orig x3200

GETC
ADD R1, R0, #0

ret
;-----------------------------------------------------------------------------------------------
; SUB_LOAD_VALUE local data
value .FILL xFFFF

.end

;===============================================================================================


;------------------------------------------------------------------------------------------
; Subroutine: SUB_PRINT_DECIMAL (Be sure to fill details in below)
;
; Parameter (R): R1
; Return Value: none
;------------------------------------------------------------------------------------------
.orig x3400
ST R7, SAVE7_3400
ST R2, SAVE2_3400
ST R3, SAVE3_3400
ST R0, SAVE0_3400
ST R5, SAVE5_3400

AND R4, R4, #0

LD R3, OperAND

AND R5, R5, #0
ADD R5, R5, #15
ADD R5, R5, #1

top
;Get First Bit
AND R2, R1, R3 ;Get MS Bit Only
BRz skip ;if MS bit is 1
ADD R4, R4, #1
skip

ADD R1, R1, R1
ADD R5, R5, #-1
BRp top

bot
LD R5, SAVE5_3400
LD R0, SAVE0_3400
LD R3, SAVE3_3400
LD R2, SAVE2_3400
LD R7, SAVE7_3400
ret
;-----------------------------------------------------------------------------------------------
; SUB_PRINT_DECIMAL local data
OperAND .FILL x8000

;BACK UPS
SAVE7_3400 .BLKW #1
SAVE2_3400 .BLKW #1
SAVE3_3400 .BLKW #1
SAVE4_3400 .BLKW #1
SAVE0_3400 .BLKW #1
SAVE5_3400 .BLKW #1

.end

