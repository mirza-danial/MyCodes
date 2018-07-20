[org 0x0100]

mov al,[x]		
mov bl,[y]
mov cl,0

sub bl,0		;;to check if y is not 0
jz B

A:
	add cl,1
	mov dl,al		;;at the end of loop al will be negative so to save previous value of al it is stored in dl
	sub al,bl
	jns A
	
sub cl,1			;;loop will execute qoutient + 1 times so to get original value of qoutient 1 is subtracted
	
	mov al,cl		;;storing qoutien to al
	mov ah,dl		;;storing remainder to ah 
B:
	
mov ax,0x4c00
int 0x21

x: db 25
y: db 13 