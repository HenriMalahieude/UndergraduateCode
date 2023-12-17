.orig x3000

AND R0, R0, #0
LD R6, arrPtr

lloopo
STR R0, R6, #0
ADD R0, R0, #1
ADD R6, R6, #1

ADD R1, R0, #-10
BRn lloopo

LD R6, arrPtr
ADD R6, R6, #6

LDR R2, R6, #0

HALT

arrPtr .FILL x4000

.end

.orig x4000
arrarrarr .BLKW 10
.end