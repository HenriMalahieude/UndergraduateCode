.ORIG x3000

LEA R0, prompt
LD R1, newline
LD R6, word

NOT R1, R1
ADD R1, R1, #1 ;negate the newline ascii value

PUTS

loop1
GETC
OUT

STR R0, R6, #0
ADD R6, R6, #1

ADD R0, R0, R1 ;character - newline = ??
BRnp loop1 ;;If R0 == 0, then last character was newline, end the loop

AND R0, R0, #0
STR R0, R6, #0

LD R0, word
PUTS

HALT

prompt .STRINGZ "Input a string\n"
newline .FILL x0A
word .FILL x4000

.END

.ORIG x4000
arr .BLKW #100
.END