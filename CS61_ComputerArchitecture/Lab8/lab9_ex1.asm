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

ADD R1, R1, #1

LD R5, SUB_PRINT_DECIMAL_ADDR
JSRR R5

halt
;-----------------------------------------------------------------------------------------------
; test harness local data:

SUB_LOAD_VALUE_ADDR .FILL x3200
SUB_PRINT_DECIMAL_ADDR .FILL x3400

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

LD R1, value

ret
;-----------------------------------------------------------------------------------------------
; SUB_LOAD_VALUE local data
value .FILL #103

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
ST R4, SAVE4_3400
ST R0, SAVE0_3400
ST R5, SAVE5_3400
ST R6, SAVE6_3400

LD R6, AsciiOffset

;Set Up - Ten Thousands
LD R2, TenThousand

LD R5, DIVIDE_ADDR
JSRR R5

ADD R3, R3, #0
BRz skip2

;Output
ADD R0, R3, #0
ADD R0, R0, R6
OUT

skip2
;Seq - Thousands
ADD R1, R4, #0

LD R2, Thousand
LD R5, DIVIDE_ADDR
JSRR R5

;Output
ADD R0, R3, #0
ADD R0, R0, R6
OUT

;Seq - Hundreds
ADD R1, R4, #0

LD R2, Hundred
LD R5, DIVIDE_ADDR
JSRR R5

;Output
ADD R0, R3, #0
ADD R0, R0, R6
OUT

;Seq - Tens
ADD R1, R4, #0

AND R2, R2, #0
ADD R2, R2, #10
LD R5, DIVIDE_ADDR
JSRR R5

;Output
ADD R0, R3, #0
ADD R0, R0, R6
OUT

;Seq - Ones
ADD R1, R4, #0

AND R2, R2, #0
ADD R2, R2, #1
LD R5, DIVIDE_ADDR
JSRR R5

;Output
ADD R0, R3, #0
ADD R0, R0, R6
OUT

LD R6, SAVE6_3400
LD R5, SAVE5_3400
LD R0, SAVE0_3400
LD R4, SAVE4_3400
LD R3, SAVE3_3400
LD R2, SAVE2_3400
LD R7, SAVE7_3400
ret
;-----------------------------------------------------------------------------------------------
; SUB_PRINT_DECIMAL local data  
AsciiOffset .FILL x30

DIVIDE_ADDR .FILL x3600
TenThousand .FILL #10000
Thousand .FILL #1000
Hundred .FILL #100

;BACK UPS
SAVE7_3400 .BLKW #1
SAVE2_3400 .BLKW #1
SAVE3_3400 .BLKW #1
SAVE4_3400 .BLKW #1
SAVE0_3400 .BLKW #1
SAVE5_3400 .BLKW #1
SAVE6_3400 .BLKW #1

.end

;DIVIDE, IN R1 (Dividing), R2(Divider) ||| OUT R3 (Answer), R4(Remainder)
.ORIG x3600
ST R7, SAVE7_3600

AND R3, R3, #0
ADD R4, R1, #0

NOT R2, R2
ADD R2, R2, #1 ;negate the divider

DIVIDE
ADD R4, R4, R2
BRnz ex
ADD R3, R3, #1
BRnzp DIVIDE

ex
NOT R2, R2
ADD R2, R2, #1
ADD R4, R4, R2

LD R7, SAVE7_3600
RET

SAVE7_3600 .BLKW #1
SAVE5_3600 .BLKW #1
SAVE6_3600 .BLKW #1
.END

