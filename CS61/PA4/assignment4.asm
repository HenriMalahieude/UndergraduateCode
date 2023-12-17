;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Henri Malahieude
; Email: hmala001@ucr.edu
; 
; Assignment name: Assignment 4
; Lab section: 25
; TA: James Luo
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=================================================================================
;THE BINARY REPRESENTATION OF THE USER-ENTERED DECIMAL NUMBER MUST BE STORED IN R4
;=================================================================================

.ORIG x3000		
;-------------
;Instructions
;-------------
beginning
LD R0, introPromptPtr
PUTS

AND R1, R1, #0 ;Just location for math
AND R2, R2, #0 ;Flag for negativity

AND R3, R3, #0 ;Loop Counter
ADD R3, R3, #5

LD R5, asciiOffset
NOT R5, R5
ADD R5, R5, #1

AND R4, R4, #0 ;Location of addition

; Get first character
GETC
OUT

;Test '\n'
LD R1, newLine
NOT R1, R1
ADD R1, R1, #1

ADD R1, R0, R1
Brz exit ; is very first character = '\n'? if so, just quit (no message)!

; Test '-'
LD R1, minus
NOT R1, R1
ADD R1, R1, #1

ADD R1, R0, R1
BRnp isPositive
ADD R2, R2, #1 ;set negative flag
BRnzp skipStart1

isPositive
LD R1, plus
NOT R1, R1
ADD R1, R1, #1

ADD R1, R0, R1
BRnp loop ;not plus, therefore number

skipStart1
GETC ;is plus, we need new input
OUT
ADD R3, R3, #-1

loop
LD R6, SUB_IS_NUMBER
JSRR R6
ADD R1, R1, #0
Brz failure ; it is not a number

;Shift up by 10
LD R6, SUB_MULTIPLY
JSRR R6

;Reduce from ascii
ADD R0, R0, R5

;Add this new number to register
ADD R4, R4, R0

;Loop Section
ADD R3, R3, #-1
Brn finish

GETC
OUT
BRnzp loop


failure
LD R1, newLine
NOT R1, R1
ADD R1, R1, #1
ADD R1, R0, R1
Brz finish ;not actually a failure, just not 5 digits

LD R0, errorMessagePtr
PUTS
Brnzp beginning

finish
ADD R2, R2, #0
BRnz justFin

NOT R4, R4
ADD R4, R4, #1

justFin
LD R0, newLine
OUT

exit HALT
;---------------	
; Program Data
;---------------

introPromptPtr  .FILL xB000
errorMessagePtr .FILL xB200

SUB_IS_NUMBER .FILL x3200
SUB_MULTIPLY .FILL x3400

asciiOffset .FILL x30
newLine .FILL x0A
minus .FILL x2D
plus .FILL x2B
.END

;------------
; Remote data
;------------
.ORIG xB000	 ; intro prompt
.STRINGZ	 "Input a positive or negative decimal number (max 5 digits), followed by ENTER\n"

.END					
					
.ORIG xB200	 ; error message
.STRINGZ	 "\nERROR: invalid input\n"

;---------------
; END of PROGRAM
;---------------
.END

;-------------------
; PURPOSE of PROGRAM
;-------------------
; Convert a sequence of up to 5 user-entered ascii numeric digits into a 16-bit two's complement binary representation of the number.
; if the input sequence is less than 5 digits, it will be user-terminated with a newline (ENTER).
; Otherwise, the program will emit its own newline after 5 input digits.
; The program must end with a *single* newline, entered either by the user (< 5 digits), or by the program (5 digits)
; Input validation is performed on the individual characters as they are input, but not on the magnitude of the number.

;Determine if it's a number or not, Input in R0, Output in R1 (0 no, 1 yes)
.orig x3200 
ST R7, SaveR7

LD R1, asciiMin
NOT R1, R1
ADD R1, R1, #1

ADD R1, R0, R1
BRn no ;negative, therfore less than asciiMin

LD R1, asciiMax
NOT R1, R1
ADD R1, R1, #1

ADD R1, R0, R1
Brp no ;positive, therfore greater than asciiMax

;Yes, is number
AND R1, R1, #0
ADD R1, R1, #1
Brnzp r

no ; not number
AND R1, R1, #0

r
LD R7, SaveR7
RET

asciiMin .FILL x30
asciiMax .FILL x39

SaveR7 .BLKW #1

.end

;---------------------------------------------------

;Multiplies R4 by 10
.orig x3400 
ST R1, BACK_R1
ST R2, BACK_R2
ST R7, BACK_R7

AND R1, R1, #0
ADD R1, R1, #9

ADD R2, R4, #0

loopMulti
ADD R4, R2, R4

ADD R1, R1, #-1
BRp loopMulti

LD R1, BACK_R1
LD R2, BACK_R2
LD R7, BACK_R7
RET

BACK_R1 .BLKW #1
BACK_R2 .BLKW #1
BACK_R7 .BLKW #1

.end

