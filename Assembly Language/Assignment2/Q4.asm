[org 0x100]

JMP START

MSK:DW 0X0001

START:

	MOV BX,0X1111
	MOV AX,0Xffff
	MOV CX,0
ITERATION:
	ROR BX,1
	JNC INCREMENT

	XOR AX,[MSK]
	SHL WORD[MSK],1
INCREMENT:
	INC CX
	CMP CX,16
	JNE ITERATION	

mov ax,0x4c00
int 0x21
