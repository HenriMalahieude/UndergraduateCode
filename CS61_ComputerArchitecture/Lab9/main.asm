.orig x3000
;this stack lab computes the polish notation of a set of calls
LD R6, stack_pointer

;push_val(4) pushes the value 4 onto the stack [4]
AND R4, R4, #0
ADD R4, R4, #4

LD R5, push_sub
JSRR R5

;push_val(3) pushes the value 3 onto the stack [4,3]
AND R4, R4, #0
ADD R4, R4, #3

LD R5, push_sub
JSRR R5

;push_val(2) pushes the value 2 onto the stack [4,3,2]
AND R4, R4, #0
ADD R4, R4, #2

LD R5, push_sub
JSRR R5

AND R4, R4, #0

;add_val() pop 3,2 and push the result of 3+2 onto the stack [4,5]
LD R5, adv_sub
JSRR R5

;add_val() pop 4,5 and push the result of 4+5 onto the stack[9]
LD R5, adv_sub
JSRR R5

;move the top value of the stack into r4
LDR R4, R6, #0
ADD R6, R6, #1

halt

push_sub .fill x3400
adv_sub .fill x3800

stack_pointer .fill xFE00

.end

;;push_val(int val)implement your push function that will push a value onto the stack
.orig x3400 
ST R7, BACK7_3400

ADD R6, R6, #-1
STR R4, R6, #0

LD R7, BACK7_3400
ret

BACK7_3400 .BLKW #1

.end

;; add_val() pops two values from the top of the stack and pushes the result of adding the poppped value into the stack
.orig x3800 
ST R7, BACK7_3800
ST R3, BACK3_3800
ST R2, BACK2_3800

LDR R3, R6, #0
ADD R6, R6, #1

LDR R2, R6, #0
ADD R6, R6, #1

ADD R2, R3, R2

ADD R6, R6, #-1
STR R2, R6, #0

LD R3, BACK3_3800
LD R2, BACK2_3800
LD R7, BACK7_3800
ret

BACK7_3800 .BLKW #1
BACK3_3800 .BLKW #1
BACK2_3800 .BLKW #1

.end