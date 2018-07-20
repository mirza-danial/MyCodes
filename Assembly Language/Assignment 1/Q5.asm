[org 0x0100]

mov ch,[row]		;;counter for 
mov cl,[col]
mov bx,0

mov si,0			;;SI being used as index counter of source array
mov di,0			;;DI being used as index counter of destination array

mov dh,0			;;storing 0 to dh to get over memory issue in dx register
mov dl,[col]		;;storing value of col to dl so dl and dh combined make sense as it stores no. of columns
add dx,dx			;;adding dx to dx makes 2dx whatever the no. of columns is it will double it



A:
	
	B:
		mov ax,[matrix + si] 	;;element of source array to be stored in ax
		mov [t + di],ax			;;element of source array stored in ax to be stored in 
		add di,2				;;incrementing index counter of destination array
		
		add si,dx				;;incrementing the value of si to get next value of matrix
		
		sub ch,1				;;decrementing loop controlling variable of inner loop
		jnz B
	
	mov ch,[row]				;;reassinging value to loop controlling variable of inner loop && outer loop starts
	add bx,2					;;value of bx increased by 2
	mov si,bx					;;after every outer loop si points at next column of first row 
	
	sub cl,1					;;decrementing loop controlling variable of outer loop
	jnz A


mov ax,0x4c00
int 0x21

matrix : dw 1,2,3,4,5,6,7,8,9,10,11,12			;;source array
t: dw 0,0,0,0,0,0,0,0,0,0,0,0					;;destination array
row: db 6
col: db 2