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