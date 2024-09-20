.ORIG x3000
LEA R6, location
LD R5, SUB_LOAD_BINARY

JSRR R5


HALT

location .BLKW #1
SUB_LOAD_BINARY .FILL x3400

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
ST R7, BACK2_R7

AND R1, R1, #0

ADD R1, R1, #15 ;Loop counter
ADD R1, R1, #1

AND R2, R2, #0  ;Value

LD R3, asciiOffset
NOT R3, R3
ADD R3, R3, #1

GETC
OUT ;discard the 'b'

loop23
GETC
OUT

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
LD R7, BACK2_R7

RET

asciiOffset .FILL x30

BACK2_R0 .BLKW #1
BACK2_R1 .BLKW #1
BACK2_R2 .BLKW #1
BACK2_R3 .BLKW #1
BACK2_R7 .BLKW #1

.END