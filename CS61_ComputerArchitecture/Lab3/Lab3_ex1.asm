;=================================================
; Name: Henri Malahieude
; Email: hmala001@ucr.edu
; 
; Lab: lab 3, ex 1
; Lab section: 25
; TA: James Luo
; 
;=================================================

.orig x3000

LD R6, ARR_PTR

LDR R3, R6, #0
LDR R4, R6, #1

ADD R3, R3, #1
ADD R4, R4, #1

STR R3, R6, #0
STR R4, R6, #1

HALT

ARR_PTR .FILL x4000

.end

.orig x4000

NEW_DEC_65 .FILL #65
NEW_HEX_41 .FILL x41

.end