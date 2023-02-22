.MODEL SMALL

.STACK 1000H

.DATA

FLAG DB 0
NL DB 13,10,"$"
NUMBER_STRING DB "00000$" 

.CODE

func PROC
	PUSH BP
	MOV BP, SP
SUB SP,2 ; i decl
MOV AX, 4[BP]
PUSH AX ; n called
;PUSH 0
MOV AX, 0
POP BX ; left side value
CMP BX, AX ; evaluating n==0
JNE L1
PUSH 1 ; if n==0 is true
JMP L0
L1:
PUSH 0 ; if n==0 is false
L0:
POP AX ; expr in AX
CMP AX, 0 ; checking expr
JE label_else_1
;PUSH 0
MOV AX, 0
	JMP func_EXIT
label_else_1: ; end if label
MOV AX, -2[BP]
PUSH AX ; i called
MOV AX, 4[BP]
;PUSH AX ; n called
;POP AX ; r-val of assignop n
MOV -2[BP], AX ; assigning n to i
POP AX
MOV AX, 4[BP]
PUSH AX ; n called
;PUSH 1
MOV AX, 1
POP BX
SUB BX, AX
PUSH BX ; n-1 pushed
CALL func
PUSH AX ; return value of func
MOV AX, -2[BP]
;PUSH AX ; i called
;POP AX
POP BX
ADD AX, BX
;PUSH AX ; func(n-1)+i pushed
;POP AX
	JMP func_EXIT
func_EXIT:
	MOV SP, BP ; Restoring SP
	POP BP
	RET 2
func ENDP

func2 PROC
	PUSH BP
	MOV BP, SP
SUB SP,2 ; i decl
MOV AX, 4[BP]
PUSH AX ; n called
;PUSH 0
MOV AX, 0
POP BX ; left side value
CMP BX, AX ; evaluating n==0
JNE L3
PUSH 1 ; if n==0 is true
JMP L2
L3:
PUSH 0 ; if n==0 is false
L2:
POP AX ; expr in AX
CMP AX, 0 ; checking expr
JE label_else_2
;PUSH 0
MOV AX, 0
	JMP func2_EXIT
label_else_2: ; end if label
MOV AX, -2[BP]
PUSH AX ; i called
MOV AX, 4[BP]
;PUSH AX ; n called
;POP AX ; r-val of assignop n
MOV -2[BP], AX ; assigning n to i
POP AX
MOV AX, 4[BP]
PUSH AX ; n called
;PUSH 1
MOV AX, 1
POP BX
SUB BX, AX
PUSH BX ; n-1 pushed
CALL func
PUSH AX ; return value of func
MOV AX, -2[BP]
;PUSH AX ; i called
;POP AX
POP BX
ADD AX, BX
;PUSH AX ; func(n-1)+i pushed
;POP AX
	JMP func2_EXIT
func2_EXIT:
	MOV SP, BP ; Restoring SP
	POP BP
	RET 2
func2 ENDP

main PROC
	MOV AX, @DATA
	MOV DS, AX
PUSH BP
MOV BP, SP
SUB SP,2 ; a decl
MOV AX, -2[BP]
PUSH AX ; a called
PUSH 7
CALL func
;PUSH AX ; return value of func
;POP AX ; r-val of assignop func(7)
MOV -2[BP], AX ; assigning func(7) to a
POP AX
MOV AX, -2[BP]
CALL PRINT
 ; argument a in AX
;PUSH 0
MOV AX, 0
	JMP main_EXIT
main_EXIT:
	MOV SP, BP ; Restoring SP
	POP BP
	MOV AH, 4CH
	INT 21H
main ENDP

PRINT PROC ; PRINTS A WORD INTEGER IN AX
	LEA SI, NUMBER_STRING ; IS 00000
    ADD SI, 5 ; START FROM ONE'S DIGIT
    CMP AX, 0
    JNL PRINT_LOOP
    MOV FLAG, 1
    NEG AX
    PRINT_LOOP:
        DEC SI
        MOV DX, 0 ; DX:AX = 0000:AX
        MOV CX, 10
        DIV CX
        ADD DL, '0'
        MOV [SI], DL
        CMP AX, 0
        JNE PRINT_LOOP
    CMP FLAG, 0
    JNG NOT_NEGATIVE
    MOV AH, 2
    MOV DL, 45
    INT 21H
    MOV FLAG, 0
	NOT_NEGATIVE:
    MOV DX, SI
    MOV AH, 9
    INT 21H
	MOV DX, OFFSET NL   ; NEWLINE
    MOV AH, 9
    INT 21H
    RET
PRINT ENDP
END MAIN
