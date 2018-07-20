[org 0x0100]


mov ax,[x]
mov dx,[x]
mov cx,[y]

sub cx,1
jz C		;;execute when cx=y=1 
			;;because x^y=x if y=1 
mov ax,1	;;storing 1 in ax 
js C		;;execute if cx=y=0 because x^y=1 if y=0 

A:			;;if y is neither 0 nor 1
	mov bx,[x]
	mov ax,0
	B:
		add ax,dx
		sub bx,1
		jnz B
	mov dx,ax
	sub cx,1
	jnz A
	
C:	
	mov [result],ax
	
mov ax,0x4c00
int 0x21

x: dw 10
y: dw 2
result: dw 0

;;logic 
;;if x=5 and y=4

;;in first iteration of A
;;5+5+5+5+5=25

;;in second iteration of A
;;25+25+25+25+25=125

;;in third iteration of A
;;125+125+125+125+125=625=5^4

;;note the inner loop(B) is executed x times while outer loop(A) is executed  y-1 times