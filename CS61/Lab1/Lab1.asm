;---------
; Malahieude, Henri
; Login: hmala001
; Section: 25
; TA: James Luo
; Lab 01
;---------

.orig x3000
;----
;Instructions
;----
AND R0, R0, #0
ADD R0, R0, #1
NOT R0, R0

LD R0, asd
JMP R0

HALT

;----
;Local Data
;----

Twelve .FILL #12
Six .FILL #6
asd .FILL x3001
TEST .STRINGZ "Hello, World!"

.end