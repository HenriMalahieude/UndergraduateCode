.ORIG x3000
LEA R6, location

LD R5, SUB_INPUT_BINARY
JSRR R5

LD R0, newline2
OUT

LD R5, SUB_OUTPUT_BINARY
JSRR R5

HALT

location .BLKW #1
newline2 .FILL x0A

;Subroutines
SUB_INPUT_BINARY .FILL x3400
SUB_OUTPUT_BINARY .FILL x3200

.END

;=========================================================================
;Parameters R6 is pointer to value, returns none, just prints out value
.ORIG x3200			; Program begins here
;-------------
;Instructions
;-------------
ST R1, UP1_R1
ST R2, UP1_R2
ST R3, UP1_R3
ST R7, UP1_R7

LDR R1, R6, #0			; R1 <-- value to be displayed as binary
LD R2, forSpace         ; R2 <-- count for space
LD R3, totalLoop        ; R3 <-- total bits to output 
;-------------------------------
;INSERT CODE STARTING FROM HERE
;--------------------------------
LD R0, binaryB
OUT

loop
ADD R1, R1, #0
BRzp pos 
LD R0, one
OUT
BRnzp forward

pos
LD R0, zero
OUT

forward
ADD R2, R2, #-1 ;Get a space outputted
BRp skip
ADD R5, R3, #-1
BRz skip
LD R0, space
OUT
ADD R2, R2, #4

skip
ADD R1, R1, R1 ;left-shift the value
ADD R3, R3, #-1 ;16-bits to output
BRp loop

LD R0, newline
OUT

LD R1, UP1_R1
LD R2, UP1_R2
LD R3, UP1_R3
LD R7, UP1_R7

RET

;---------------	
;Data
;---------------
zero .FILL x30
one .FILL x31
newline .FILL x0A
binaryB .FILL #98
space .FILL x20
totalLoop .FILL #16
forSpace .FILL #4

;---------------
;Back Up
;---------------
UP1_R1 .BLKW #1
UP1_R2 .BLKW #1
UP1_R3 .BLKW #1
UP1_R7 .BLKW #1

.END

;----------------------------------------------------
;----------------------------------------------------
;Parameters R6 pointer to location
;Returns nothing (but R6 memory is changed)
.ORIG x3400
ST R0, BACK2_R0
ST R1, BACK2_R1
ST R2, BACK2_R2
ST R3, BACK2_R3
ST R4, BACK2_R4
ST R7, BACK2_R7

startAgain
AND R1, R1, #0

ADD R1, R1, #15 ;Loop counter
ADD R1, R1, #1

AND R2, R2, #0  ;Value

LD R3, asciiOffset
NOT R3, R3
ADD R3, R3, #1

GETC
OUT

LD R4, binaryB2
NOT R4, R4
ADD R4, R4, #1

ADD R0, R0, R4
BRz loop23

fail
LEA R0, incorrectOutput
PUTS
BRnzp startAgain

loop23
GETC
OUT

LD R4, space2
NOT R4, R4
ADD R4, R4, #1
ADD R4, R0, R4
Brz loop23

ADD R4, R0, R3 ;reduce it to 0 or 1
ADD R4, R4, #-2 ; 0 and 1 will always be negative after addition with -2
BRzp fail

test
ADD R0, R0, R3 ;reduce it to 0 or 1
ADD R2, R2, R2 ;left shift
ADD R2, R2, R0 ;add the 1 or zero

ADD R1, R1, #-1
BRp loop23

STR R2, R6, #0

LD R0, BACK2_R0
LD R1, BACK2_R1
LD R2, BACK2_R2
LD R3, BACK2_R3
LD R4, BACK2_R4
LD R7, BACK2_R7

RET

asciiOffset .FILL x30
space2 .FILL x20
binaryB2 .FILL #98
incorrectOutput .STRINGZ "\nInvalid input, try again\n"

BACK2_R0 .BLKW #1
BACK2_R1 .BLKW #1
BACK2_R2 .BLKW #1
BACK2_R3 .BLKW #1
BACK2_R4 .BLKW #1
BACK2_R7 .BLKW #1

.END