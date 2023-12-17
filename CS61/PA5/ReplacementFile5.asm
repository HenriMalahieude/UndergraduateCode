; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Henri Malahieude
; Email: hmala001@ucr.edu
; 
; Assignment name: Assignment 5
; Lab section: 25
; TA: James Luo
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=================================================================================
; PUT ALL YOUR CODE AFTER THE main LABEL
;=================================================================================

;---------------------------------------------------------------------------------
;  Initialize program by setting stack pointer and calling main subroutine
;---------------------------------------------------------------------------------
.ORIG x3000

; initialize the stack
ld r6, stack_addr

; call main subroutine
LEA R5, main
JSRR R5

;---------------------------------------------------------------------------------
; Main Subroutine
;---------------------------------------------------------------------------------
main
; get a string from the user
LEA R1, user_prompt
LEA R2, user_string
LD R5, get_user_string_addr
JSRR R5

; find size of input string
LEA R1, user_string
LD R5, strlen_addr
JSRR R5

; call palindrome method
LEA R7, user_string
ADD R2, R1, R0
ADD R2, R2, #-1 
LD R5, palindrome_addr
JSRR R5

ADD R1, R0, #0

LEA R0, result_string
PUTS

ADD R1, R1, #0
BRp pp

LEA R0, not_string
PUTS

pp

LEA R0, final_string
PUTS

HALT

;---------------------------------------------------------------------------------
; Required labels/addresses
;---------------------------------------------------------------------------------

; Stack address ** DO NOT CHANGE **
stack_addr           .FILL    xFE00

; Addresses of subroutines, other than main
get_user_string_addr .FILL    x3200
strlen_addr          .FILL    x3300
palindrome_addr      .FILL	  x3400

; Reserve memory for strings in the progrtam
user_prompt          .STRINGZ "Enter a string: "
result_string        .STRINGZ "The string is "
not_string           .STRINGZ "not "
final_string         .STRINGZ "a palindrome\n"

; Reserve memory for user input string
user_string          .BLKW	  100

.END

;---------------------------------------------------------------------------------
; get_user_string - Lets the user input a string until newline input
;
; parameter: R1 - Prompt Location
; parameter: R2 - Location to save Word
;
; returns: nothing, is saved in R2
;---------------------------------------------------------------------------------
.ORIG x3200
get_user_string
; Backup all used registers, R7 first, using proper stack discipline
ADD R7, R6, #-1 ;Register 7
STR R7, R6, #0

ADD R6, R6, #-1 ;Register 0
STR R0, R6, #0

ADD R6, R6, #-1 ;Register 3
STR R3, R6, #0

;Load information
ADD R0, R1, #0 ;Input prompt
PUTS ;show prompt

LD R3, newline ;sentinel
NOT R3, R3 
ADD R3, R3, #1 ;negate the newline ascii value, for sentinel

;Get string
loop1
GETC
OUT

STR R0, R2, #0 ;store value into array
ADD R2, R2, #1

ADD R0, R0, R3 ;character - newline = ??
BRnp loop1 ;If R0 == 0, then last character was newline, end the loop

ADD R2, R2, #-1 ;we are overwriting the newline
AND R0, R0, #0
STR R0, R2, #0 ;store null-termination after newline

LDR R3, R6, #0
ADD R6, R6, #1 ;Register 3

LDR R0, R6, #0
ADD R6, R6, #1 ;Register 0

LDR R7, R6, #0
ADD R6, R6, #1 ;Register 7
RET

newline .FILL x0A

.END

;---------------------------------------------------------------------------------
; strlen- counts characters in string
;
; parameter: R1 - Address of the string
;
; returns: Returned in R0
;---------------------------------------------------------------------------------
.ORIG x3300
strlen
; Backup all used registers, R7 first, using proper stack discipline
ADD R6, R6, #-1 ;Register 7
STR R7, R6, #0

ADD R6, R6, #-1 ;Register 2
STR R2, R6, #0

AND R0, R0, #0

loop_3300
LDR R2, R1, #0
BRnz exit_3300

ADD R1, R1, #1
ADD R0, R0, #1
BRzp loop_3300
exit_3300

; Restore all used registers, R7 last, using proper stack discipline
LDR R2, R6, #0
ADD R6, R6, #1 ;Register 2

LDR R7, R6, #0
ADD R6, R6, #1 ;Register 7
RET

.END

;---------------------------------------------------------------------------------
; palindrome - recursively checks if string is a palindrome
;
; parameter: R1 - address of first character
; parameter: R2 - address of last character
;
; returns: R0, boolean for yes or no
;---------------------------------------------------------------------------------
.ORIG x3400
palindrome ; Hint, do not change this label and use for recursive alls
; Backup all used registers, R7 first, using proper stack discipline
ADD R6, R6, #-1 ;Register 7
STR R7, R6, #0

ADD R6, R6, #-1 ;Register 3
STR R3, R6, #0

ADD R6, R6, #-1 ;Register 4
STR R4, R6, #0

;Recursive Code

;Base Case
NOT R4, R2
ADD R4, R4, #1

ADD R3, R1, R4
BRzp yes_3400 ;check that they aren't the same/past each other

;Load Elements
LDR R3, R1, #0
LDR R4, R2, #0
NOT R4, R4
ADD R4, R4, #1

ADD R3, R3, R4 ;Compare elements
BRz jump_3400 ;If not zero, then it's not a palindrome
BRnp no_3400

yes_3400
AND R0, R0, #0
ADD R0, R0, #1
BRnzp exit_3400

no_3400
AND R0, R0, #0
BRnzp exit_3400

jump_3400
ADD R1, R1, #1
ADD R2, R2, #-1
JSR palindrome

; Restore all used registers, R7 last, using proper stack discipline
exit_3400
LDR R4, R6, #0
ADD R6, R6, #1 ;Register 4

LDR R3, R6, #0
ADD R6, R6, #1 ;Register 3

LDR R7, R6, #0
ADD R6, R6, #1 ;Register 7
RET

.END