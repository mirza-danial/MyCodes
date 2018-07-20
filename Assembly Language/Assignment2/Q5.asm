[org 0x100]

JMP START

MASK1: 	DB	0XFF
MASK2:	DB  0xFF
 	
BIT:	DW 100
BUFFER: DB 219,26,207,96,251,12,34,56,211,234,123,2,123,220,43,99,103,43,54,45,54,65,76,55,223,55,190,34,65,87,97,86

START:
	MOV CX,8
	MOV AX,[BIT]
	DIV CX						;;RESULT IN AX REMAINDER IN DX
		
	MOV BX,AX					;; MOVING RESULT IN BX
	
	MOV CL,[BUFFER+BX]
	AND [MASK1],CL		 		;;MOVING DATA IN MASK1
		
	MOV CX,DX					;;MOVING REMAINDER IN CX
		
SHIFTLEFT:
	CMP CX,0
	JE END1
	SHL BYTE[MASK1],1
	DEC CX
	JMP SHIFTLEFT
END1:
	INC BX
	MOV CL,[BUFFER+BX]
	AND [MASK2],CL

	MOV CX,DX

SHIFTRIGHT:
	CMP CX,8
	JE END2
	SHR BYTE[MASK2],1
	INC CX
	JMP SHIFTRIGHT
		
END2:
	
	MOV AX,0
	MOV AL,[MASK1]
	ADD AL,[MASK2]


mov ax,0x4c00
int 0x21

;;PROGRAM LOGIC
;First of all the given starting bit is divided by 8 to get remainder and qoutient
;e.g. if given byte is 100 qoutient will be 12 and remainder will be 4
;Qoutient tells us about the starting byte of buffer from which data should be extracted
;e.g. [buffer+12] will be the byte containing data from 96-103
;Remainder tells us about the starting bit of that byte from which data should be extracted
;e.g. in above example our required data will start from 4th bit means 96+4= 100th bit
;The whole byte is copied in MSK1 
;e.g.whole data from 96th to 103rd bit will be copied in [msk1]
;Using remainder Msk1 is shifted to left so that only required bits remain in Msk1
;e.g. [msk1] will be shifted to left 4 times to get 100th bit as MSB of [msk1]
;Now next whole byte is copied in Msk2 
;e.g. byte from 104th bit to 111th bit will be copied in [msk2]
;Now Msk2 is shifted towards right 8-remainder times to get only required bits
;e.g. [msk2] will be shifted toward right 8-4=4 times to get 107th bit as LSB of [msk2]
;Msk1 is moved in al
;e.g. obtaing data from 100th bit to 103rd th bit in al 
;Msk 2 is added in al
;e.g. obtaining data from 104th to 107th bit in al
;al stores a byte from buffer starting from given bit
; e.g al has data from 100th bit to 107th bit

