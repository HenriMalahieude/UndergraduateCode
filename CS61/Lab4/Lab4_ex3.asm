.orig x3000

AND R0, R0, #0
ADD R0, R0, #1 ;hardcoded 1 for 2^0

AND R1, R1, #0

LD R6, arrPtr

;ma homeboi 1
lloopo
STR R0, R6, #0
ADD R0, R0, R0
ADD R6, R6, #1

ADD R1, R1, #1
ADD R3, R1, #-10
BRn lloopo

ADD R6, R6, #-4
LDR R2, R6, #0


HALT

arrPtr .FILL x4000

.end

.orig x4000
arrarrarr .BLKW 10
.end