.orig x3000

LD R0, curLetter
LD R1, loopCount

Loo OUT
    ADD R0, R0, #1
    ADD R1, R1, #-1
    BRp Loo

HALT

curLetter .FILL x61
loopCount .FILL x1A

.end