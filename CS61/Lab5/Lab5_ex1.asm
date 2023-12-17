.orig x3000
LD R1, wordPtr

LD R6, SUB_GET_STRING
JSRR R6

;LD R0, wordPtr
;PUTS

LD R6, SUB_TO_UPPER
JSRR R6

;LD R0, wordPtr
;PUTS

LD R6, SUB_IS_PALI
JSRR R6

;LD R6, TO_ASCII
;ADD R0, R4, R6
;OUT

ADD R4, R4, #0
BRz oN

LEA R0, Yes_S
PUTS
BRnzp h

oN
LEA R0, No_S
PUTS

h
HALT

wordPtr .FILL x3100
SUB_GET_STRING .FILL x3200
SUB_IS_PALI .FILL x3400
SUB_TO_UPPER .FILL x3600
TO_ASCII .FILL x30

Yes_S .STRINGZ "This is a palindrome!"
No_S .STRINGZ "This is NOT a palindrome. :C"

.end

.orig x3100

word .BLKW #100

.end

;=======================================================================
; Subroutine: SUB_GET_STRING_3200
; Parameter: R1 as starting address of array
; Postcondition: [a short description of what the subroutine accomplishes]
; Return Value: R5, the number of characters read by subroutine
;=======================================================================
.orig x3200 ; use the starting address as part of the sub name
;========================
; Subroutine Instructions
;========================
;Back up the registers
ST R0, BACKUP_R0_3200
ST R1, BACKUP_R1_3200
ST R6, BACKUP_R6_3200
ST R7, BACKUP_R7_3200

;Load information
LEA R0, prompt ;Prompt
LD R6, newline ;sentinel
NOT R6, R6 
ADD R6, R6, #1 ;negate the newline ascii value, for sentinel

PUTS ;show prompt

;Get string
loop1
GETC
OUT

STR R0, R1, #0 ;store value into array
ADD R1, R1, #1

ADD R0, R0, R6 ;character - newline = ??
BRnp loop1 ;;If R0 == 0, then last character was newline, end the loop

ADD R1, R1, #-1 ;we are overwriting the newline
AND R0, R0, #0
STR R0, R1, #0 ;store null-termination after newline

;Calculate R5, output
LD R0, BACKUP_R1_3200
NOT R0, R0
ADD R0, R0, #1
ADD R5, R1, R0 ;Negate them to see output

;Load Backups
LD R0, BACKUP_R0_3200 
LD R1, BACKUP_R1_3200 
LD R6, BACKUP_R6_3200 
LD R7, BACKUP_R7_3200 

RET ;return from code

prompt .STRINGZ "Input a string\n"
newline .FILL x0A

;========================
; Subroutine Backups
;========================
BACKUP_R0_3200 .BLKW #1 ; Do this for R7 & each register that the subroutine changes
BACKUP_R1_3200 .BLKW #1
BACKUP_R6_3200 .BLKW #1
BACKUP_R7_3200 .BLKW #1 ; ... EXCEPT for Return Value(s)

.END

;=======================================================================
; Subroutine: SUB_IS_PALI_3200
; Parameter: R1 is address of a null-terminated string
; Parameter: R5 number of characters in address
; Postcondition: [a short description of what the subroutine accomplishes]
; Return Value: R4, 1 if true, 0 if false
;=======================================================================
.orig x3400
;Back Up
ST R1, BACK_R1
ST R2, BACK_R2
ST R3, BACK_R3
ST R5, BACK_R5
ST R6, BACK_R6
ST R7, BACK_R7

AND R2, R2, #0 ;loop counter

loop
ADD R3, R5, #0 ;just do R3 <-- (R5) [size of string]
ADD R3, R3, #-1 ;this will be used as offset

NOT R2, R2
ADD R2, R2, #1 ;negate r2
ADD R3, R3, R2 ; R3 - R2

ADD R4, R3, R2 ;sub it again
BRnz Yes_Pali

NOT R2, R2
ADD R2, R2, #1 ;back to positive

ADD R1, R1, R2
LDR R6, R1, #0 ;load first character

LD R1, BACK_R1 ;reset
ADD R1, R1, R3
LDR R3, R1, #0 ;load comparitor char

LD R1, BACK_R1 ;rest

NOT R6, R6
ADD R6, R6, #1

ADD R4, R3, R6 ;R3 - R5
BRnp No_Pali

ADD R2, R2, #1
BRnzp loop

No_Pali
AND R4, R4, #0
BRnzp rr

Yes_Pali
AND R4, R4, #0
ADD R4, R4, #1

rr
LD R1, BACK_R1
LD R2, BACK_R2
LD R3, BACK_R3
LD R5, BACK_R5
LD R6, BACK_R6
LD R7, BACK_R7
RET

BACK_R1 .BLKW #1
BACK_R2 .BLKW #1
BACK_R3 .BLKW #1
BACK_R5 .BLKW #1
BACK_R6 .BLKW #1
BACK_R7 .BLKW #1

.end

;-------------------------------------------------------------------------
; Subroutine: SUB_TO_UPPER
; Parameter (R1): Starting address of a null-terminated string
; Postcondition: The subroutine has converted the string to upper-case
; in-place i.e. the upper-case string has replaced the original string
; No return value, no output, but R1 still contains the array address, unchanged
;-------------------------------------------------------------------------
.orig x3600
ST R1, BACK-U_R1
ST R2, BACK-U_R2
ST R3, BACK-U_R3
ST R7, BACK-U_R7

AND R2, R2, #0

LD R3, mask
NOT R3, R3

loop2
LDR R2, R1, #0
BRz rr2

NOT R2, R2
AND R2, R2, R3
NOT R2, R2 ; This should be 'or' right?
STR R2, R1, #0

ADD R1, R1, #1
BRnzp loop2

rr2
LD R1, BACK-U_R1
LD R2, BACK-U_R2
LD R3, BACK-U_R3
LD R7, BACK-U_R7

RET

mask .FILL x0020

BACK-U_R1 .BLKW #1
BACK-U_R3 .BLKW #1
BACK-U_R2 .BLKW #1
BACK-U_R7 .BLKW #1
.end
