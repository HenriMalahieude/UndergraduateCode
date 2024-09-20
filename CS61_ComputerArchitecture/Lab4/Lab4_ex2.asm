.orig x3000

AND R0, R0, #0
AND R1, R1, #0
AND R2, R2, #0
LD R6, arrPtr

lloopo
STR R0, R6, #0
ADD R0, R0, #1
ADD R6, R6, #1

ADD R1, R0, #-10
BRn lloopo

;reset for new output loop
AND R0, R0, #0
AND R1, R1, #0
ADD R6, R6, #-10
LD R5, asciiOffset

loop22
LDR R0, R6, #0

;Switch Ascii
ADD R0, R0, R5

OUT
ADD R6, R6, #1

ADD R1, R1, #1
ADD R2, R1, #-10
BRn loop22

HALT

arrPtr .FILL x4000
asciiOffset .Fill x30

.end

.orig x4000
arrarrarr .BLKW 10
.end