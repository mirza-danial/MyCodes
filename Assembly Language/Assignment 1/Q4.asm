[org 0x0100]

mov ax,[n1]		
mov bx,[n2]

sub bx,ax
js A			;; n2 is smaller than n1 no need of swap
	
mov bx,[n2]		;;swapping n1 and n2	
mov [n1],bx
mov [n2],ax	
	
A:	
	mov bx,1			;;bx be i in question c++ program
	mov cx,[n2]
	B:
		mov ax,[n1]
		mov dx,[n2]
		C:
			sub ax,bx
			jns C
	
		add ax,bx			;;ax=ax%bx 
		
		D:
			sub dx,bx
			jns D
			
		add dx,bx			;;dx=dx%bx
			
		add ax,dx			;;AND operation on ax and dx 
		jnz E				;;ax+dx will be 0 iff ax and dx both are zero as ax or dx cannot be negative
		
		mov [hcf],bx		;;if bx is factor of ax and dx it is stored in hcf
		
		E:
			add bx,1		;;bx increased
			sub cx,1		;;loop controlling variable decreased
			jnz B			
	
mov ax,0x4c00
int 0x21

n1:dw 54
n2:dw 24
hcf: dw 0