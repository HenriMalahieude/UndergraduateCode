.ORIG x3000

LEA R0, prompt
LD R1, loopTotal
LEA R6, array_start

PUTS

loop
GETC
OUT

STR R0, R6, #0
ADD R6, R6, #1

LD R0, newline
OUT

ADD R1, R1, #-1
BRp loop

HALT

prompt .STRINGZ "Enter 10 Characters\n"
newline .FILL x0A
loopTotal .FILL #10
array_start .BLKW #10

.END