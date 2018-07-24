[org 0x100]
jmp start
winMessage	: db 'You Win!'					;length=8
loseMessage	: db 'You Lose:('				;length=10
pointMessage: db 'Points :'					;length=8
bonusMessage: db 'Bonus  :'					;length=8
totalPoints : db 'Total  :'					;length=8
oldisr : dd 0								;Timer ISR	
oldisr1: dd 0								;KBISR

reflectorStart: dw 3750						;Start Index of bar
reflectorEnd:dw 3772						;End Index of bar
reflectorMid:dw 3760						;Mid Index of bar	
attribute: db 0xFF							;Attribute of bar

screen_attribute: db 0x0F					;Background Screen Atrribute

patternStart: dw 484						;Brick Pattern Start
patterAttribute: db 0x3F					;Bricks Attribute
patternLength: dw 10						;Length of each brick
noOfBricks: dw 10							;Total number of bricks
ballAtrribute: dw 0x0f

time_delayer: dw 0							;
ball_delayer: dw 0							;

GameEnd: dw 0								;1: Game has ended 0:Game isn't ended

life: dw 3									;No. of lives
min : dw 0									;Minutes counter
sec : dw 0									;Second counter
points: dw 0
bonus : dw 0								;1: bonus will be given 0: bonus will not be given
win	: dw 0									;1:Player won  0:Player lose
bonuspoints: dw 0							;Bonus points

currentPosition: dw  3600					;Position of ball
; 1. move 90 degree upwards
; 2. move 90 degree downwards
; 3. move 45 degree upwards
; 4. move 45 degree downwards
; 5. move 135 degree upwards
; 6. move 135 degree downwards
movement: 		 dw  1						;Movement Directions
ball: 			 db 7						;Character used as ball

movfast: dw 3							;Speed of ball

Powercharacter: db 1
PowerBool:		dw 0
PowerPositions: dw 0
PowerTimer:		dw 0
PowerTimeBool:	dw 0

power_delayer:  dw 0

Fireball_mov :  dw 0
fireball_timer: dw 0
fireball_bool: 	dw 0 
;<----------------------------- Print Message----------------------------->
;Prints game details at the end of the game
PrintMessage:
			push ax
			push bx
			push cx
			push dx
			push bp
			push di
			push es
			
			mov byte[screen_attribute],0x3F
			call clrscr
			
			call border
			cmp word[win],1
			jne PMcon1
			
			mov ah,13h
			mov al,1
			mov bh,0
			mov bl,[screen_attribute]
			mov dh, 10
			mov dl,	35
			mov cx,8
			push cs
			pop es
			mov bp,winMessage
			int 0x10
			jmp PMcon2
PMcon1:
			mov ah,13h
			mov al,1
			mov bh,0
			mov bl,[screen_attribute]
			mov dh, 10
			mov dl,	35
			mov cx,10
			push cs
			pop es
			mov bp,loseMessage
			int 0x10
			jmp PMcon2
PMcon2:
			mov ah,13h
			mov al,1
			mov bh,0
			mov bl,[screen_attribute]
			mov dh, 11
			mov dl,	35
			mov cx,8
			push cs
			pop es
			mov bp,pointMessage
			int 0x10
		
			mov ax,11
			mov bl,80
			mul bl
			add ax,35
			add ax,8
			shl ax,1
			mov di,ax
			
			push word[points]
			call printnum
			
			
			mov ah,13h
			mov al,1
			mov bh,0
			mov bl,[screen_attribute]
			mov dh, 12
			mov dl,	35
			mov cx,8
			push cs
			pop es
			mov bp,bonusMessage
			int 0x10
			
			mov ax,12
			mov bl,80
			mul bl
			add ax,35
			add ax,8
			shl ax,1
			mov di,ax
			
			push word[bonuspoints]
			call printnum
			
			mov ah,13h
			mov al,1
			mov bh,0
			mov bl,[screen_attribute]
			mov dh, 13
			mov dl,	35
			mov cx,8
			push cs
			pop es
			mov bp,totalPoints	
			int 0x10
			
			mov ax,13
			mov bl,80
			mul bl
			add ax,35
			add ax,8
			shl ax,1
			mov di,ax
			
			mov ax,[points]
			add ax,[bonuspoints]
			push ax
			call printnum
			
			pop es
			pop di
			pop bp
			pop dx
			pop cx
			pop bx
			pop ax
			
			ret

;<----------------------------- Print Number----------------------------->
;Prints a number
			
printnum: 	push bp
			mov bp, sp
			push es
			push ax
			push bx
			push cx
			push dx
			;push di
			
			mov ax, 0xb800
			mov es, ax ; point es to video base
			mov ax, [bp+4] ; load number in ax
			mov bx, 10 ; use base 10 for division
			mov cx, 0 ; initialize count of digits

nextdigit: 	mov dx, 0 ; zero upper half of dividend
			div bx ; divide by 10
			add dl, 0x30 ; convert digit into ascii value
			push dx ; save ascii value on stack
			inc cx ; increment count of values
			cmp ax, 0 ; is the quotient zero
			jnz nextdigit ; if no divide it again
			;mov di, 0

nextpos: 	pop dx ; remove a digit from the stack
			mov dh, [screen_attribute] ; use normal attribute
			mov [es:di], dx ; print char on screen
			add di, 2 ; move to next screen location
			loop nextpos ; repeat for all digits on stack
			
			;pop di
			pop dx
			pop cx
			pop bx
			pop ax
			pop es
			pop bp
			ret 2
;<----------------------------- Display Time----------------------------->
;Display time at the top left corner

displayTime:
	push ax
	push bx
	push cx
	push dx
	push si
	push di
	push es
	
	mov ax,0xb800
	mov es,ax
	mov ah,[screen_attribute]
	
	mov di,2
	
	mov al,'T'
	mov [es:di],ax
	add di,2
	
	mov al,'i'
	mov [es:di],ax
	add di,2
	
	mov al,'m'
	mov [es:di],ax
	add di,2
	
	mov al,'e'
	mov [es:di],ax
	add di,2
	
	mov al,':'
	mov [es:di],ax
	add di,4
	
	mov ax,[min]
	push ax
	call printnum
	
	
	
	mov ah,[screen_attribute]
	mov al,':'
	mov [es:di],ax
	add di,2
	
	mov ax,[sec]
	push ax
	call printnum
	
	inc word[sec]
	cmp word[sec],60
	jne ExitTimeDis
	mov word[sec],0
	inc word[min]
	
ExitTimeDis:	
	pop es
	pop di
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
	
	ret		
	
;<----------------------------- Print Points----------------------------->
;Prints points earned at top
displayPoints:
	
	push ax
	push bx
	push cx
	push dx
	push si
	push di
	push es
	
	mov ax,0xb800
	mov es,ax
	mov ah,[screen_attribute]
	
	mov di,70
	
	mov al,'P'
	mov [es:di],ax
	add di,2
	
	mov al,'o'
	mov [es:di],ax
	add di,2
	
	mov al,'i'
	mov [es:di],ax
	add di,2
	
	mov al,'n'
	mov [es:di],ax
	add di,2
	
	mov al,'t'
	mov [es:di],ax
	add di,2
	
	mov al,'s'
	mov [es:di],ax
	add di,2
	
	mov al,':'
	mov [es:di],ax
	add di,4
	
	mov ax,[points]
	push ax
	call printnum


	
ExitPointsDis:	
	pop es
	pop di
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
	
	ret		

;<----------------------------- Display Lives ----------------------------->
;Prints no of remaining lives on top right corner
displayLifes:
	push ax
	push bx
	push cx
	push dx
	push si
	push di
	push es
	
	mov ax,0xb800
	mov es,ax
	mov ah,[screen_attribute]
	
	mov di,142
	
	mov al,'L'
	mov [es:di],ax
	add di,2
	
	mov al,'i'
	mov [es:di],ax
	add di,2
	
	mov al,'v'
	mov [es:di],ax
	add di,2
	
	mov al,'e'
	mov [es:di],ax
	add di,2
	
	mov al,'s'
	mov [es:di],ax
	add di,2
	
	
	mov al,':'
	mov [es:di],ax
	add di,4
	
	mov ax,[life]
	push ax
	call printnum


	
ExitLifeDis:	
	pop es
	pop di
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
	
	ret		

;<----------------------------- Display top bar ----------------------------->
;Prints top details line during game 
Display:
	push ax
	push bx
	push cx
	push dx
	push si
	push di
	push es
	
	mov ax,0xb800
	mov es,ax
	
	mov ah,[screen_attribute]
	mov al,' '
	mov cx,80
	mov di,0
	cld
	rep stosw
	
	
	call displayTime
	call displayPoints
	call displayLifes
	
	pop es
	pop di
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
	
	ret



;<----------------------------- Destroy Brick----------------------------->
;Destroy brick and update variables accordingly

Destroy:
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push si
	push di
	push es
	
	mov ax,0xb800
	mov es,ax
	
	mov di,[bp+4]
	
	mov ah,[patterAttribute]
	mov al,' '
	
	cld
	mov cx,0xffff
	repe scasw
	
	mov ax,0xffff
	sub ax,cx
	mov cx,ax
	
	mov di,[bp+4]
	mov ah,[screen_attribute]
	mov al,' '
	
	rep stosw
	
	
	mov di,[bp+4]
	sub di,2
	
	mov ah,[patterAttribute]
	mov al,' '
	
	std
	mov cx,0xffff
	repe scasw
	
	mov ax,0xffff
	sub ax,cx
	mov cx,ax
	
	mov di,[bp+4]
	sub di,2
	mov ah,[screen_attribute]
	mov al,' '
	
	rep stosw
	
	add word[points],10
	
	DEC WORD[noOfBricks]
	CALL BEEP
	
	cmp word[noOfBricks],0
	jne fastcond
	mov word[win],1
	mov word[GameEnd],1
	cmp word[min],2
	jae fastcond
	mov word[bonuspoints],50

fastcond:	
	cmp word[noOfBricks],8
	jne fireball_cond
	
	
	
	mov word[PowerBool],1
	mov ax,[bp+4]
	mov word[PowerPositions],ax

fireball_cond:
	cmp word[noOfBricks],5
	jne LastConditon
	
	
	mov word[Fireball_mov],1
	mov ax,[bp+4]		
	mov word[PowerPositions],ax
LastConditon:
	cmp word[noOfBricks],2
	jne ExitDestroy
	sub word[movfast],1
	
	
ExitDestroy:	
	pop es
	pop di
	pop si
	pop cx
	pop bx
	pop ax

	pop bp
	ret 2

;<----------------------------- Reduce Life----------------------------->
;Reduces a life	
reduceLife:
	sub word[life],1
	call Sound
	cmp word[life],0
	ja ExitReduceLife
	mov word[GameEnd],1

ExitReduceLife:	
	ret
	
;<----------------------------- Restart Game----------------------------->
;Restarts game after life is lost
restart:
	push ax
	push bx
	push cx
	push dx
	push di
	push es

	cmp word[GameEnd],1
	je ExitRestart
	mov ax,0xb800
	mov es,ax
	
	mov ah,[screen_attribute]
	mov al,0x20
	mov cx,78
	mov di,3836
	
	std
	rep stosw
	
	mov word[fireball_bool],0
	mov byte[ballAtrribute],0x0f
	
	mov word[reflectorStart], 3750
	mov	word[reflectorEnd], 3772
	mov word[reflectorMid],3760
	mov byte[attribute],0xFF
	mov word[PowerTimer],0
	mov word[PowerTimeBool],0
	mov word[PowerBool],0
	call create
	mov word[currentPosition],3600
	mov word[movement],1
	
	
ExitRestart:	
	pop es
	pop di
	pop dx
	pop cx
	pop bx
	pop ax
	
	ret
	
;<----------------------------- Find Next Position----------------------------->
;*Calculate next position *update ball position *call helper functions
nextposition:
	push ax
	push bx
	push cx
	push dx
	push si
	push di
	push es
	
	mov ax,0xb800
	mov es,ax
	
	mov si,[currentPosition]
	mov dx,[movement]
	
	cmp dx,1
	jne nextcond
	mov di,si
	sub di,160
	mov ah,[patterAttribute]
	mov al,' '
	
	cmp [es:di],ax
	jne a1
	
	push di
	call Destroy
	cmp word[fireball_bool],1
	je a11
	
	mov word[movement],2
	call nextposition
	
	a11:
	jmp ExitNextPosition 
	a1:
	mov ah,[screen_attribute]
	mov al,'-'
	cmp [es:di],ax
	jne a2
	mov word[movement],2
	call nextposition
	jmp ExitNextPosition 
	
	
	a2:
	mov ah,[screen_attribute]
	mov al,' '
	mov [es:si],ax
	mov ah,[ballAtrribute]
	mov al,[ball]
	mov [es:di],ax
	mov [currentPosition],di
	jmp ExitNextPosition
	
nextcond:
	cmp dx,2
	jne nextcond1
	
	mov di,si
	add di,160
	mov ah,[attribute]
	mov al,' '
	cmp [es:di],ax
	jne b1
	
	cmp di,[reflectorStart]
	jne b11
	mov word[movement],5
	jmp b13
	
	b11:
	cmp di,[reflectorEnd]
	jne b12
	mov word[movement],3
	jmp b13
	
	b12:
	
	mov word[movement],1
	
	b13:
	call nextposition
	
	jmp ExitNextPosition 
	b1:
	mov ah,[screen_attribute]
	mov al,'-'
	cmp [es:di],ax
	jne b2
	;mov word[movement],2
	;call nextposition
	call reduceLife
	call restart
	jmp ExitNextPosition 
	
	b2:
	mov ah,[screen_attribute]
	mov al,' '
	mov [es:si],ax
	mov ah,[ballAtrribute]
	mov al,[ball]
	mov [es:di],ax
	mov [currentPosition],di
	jmp ExitNextPosition

	
nextcond1:
	cmp dx,3
	je awaen3
	jmp nextcond2
awaen3:	
	mov di,si
	sub di,160
	add di,2
	
	mov ah,[patterAttribute]
	mov al,' '
	
	cmp [es:di],ax
	jne c1
	
	push di
	call Destroy
	cmp word[fireball_bool],1
	je c11
	mov word[movement],4
	call nextposition
	c11:
	jmp ExitNextPosition 
	c1:
	mov ah,[screen_attribute]
	mov al,'-'
	cmp [es:di],ax
	jne c2
	mov word[movement],4
	call nextposition
	jmp ExitNextPosition 
	
	c2:
	mov ah,[screen_attribute]
	mov al,'|'
	cmp [es:di],ax
	jne c3
	mov word[movement],5
	call nextposition
	jmp ExitNextPosition 
	
	c3:
	mov bx,si
	add bx,2
	mov ah,[patterAttribute]
	mov al,' '
	cmp [es:bx],ax
	jne c4
	push bx
	call Destroy
	cmp word[fireball_bool],1
	je c31
	mov word[movement],5
	call nextposition
	c31:
	jmp ExitNextPosition 
	
	c4:
	mov ah,[screen_attribute]
	mov al,' '
	mov [es:si],ax
	mov ah,[screen_attribute]
	mov ah,[ballAtrribute]
	mov al,[ball]
	mov [es:di],ax
	mov [currentPosition],di
	
	jmp ExitNextPosition

nextcond2:
	cmp dx,4
	je awaen
	jmp nextcond3
awaen:
	
	mov di,si
	add di,160
	add di,2
	mov ah,[patterAttribute]
	mov al,' '
	
	cmp [es:di],ax
	jne d1
	
	push di
	call Destroy
	
	cmp word[fireball_bool],1
	je d11
	mov word[movement],3
	call nextposition
	
	d11:
	jmp ExitNextPosition 
	d1:
	mov ah,[screen_attribute]
	mov al,'|'
	cmp [es:di],ax
	jne d2
	mov word[movement],6
	call nextposition
	jmp ExitNextPosition 
	
	d2:
	mov ah,[attribute]
	mov al,' '
	cmp [es:di],ax
	jne d3
	
	cmp di,[reflectorMid]
	ja d21
	jb d22
	mov word[movement],1
	jmp d23
	d21:
	mov word[movement],3
	jmp d23
	d22:
	mov word[movement],5
	jmp d23
	
	
	d23:
	
	call nextposition
	jmp ExitNextPosition
	
	d3:
	mov ah,[screen_attribute]
	mov al,'-'
	cmp [es:di],ax
	jne d4
	call reduceLife
	call restart
	jmp ExitNextPosition
	
	d4:
	mov ah,[patterAttribute]
	mov al,' '
	
	cmp [es:si+2],ax
	jne d5
	
	mov ax,si
	add ax,2
	push ax
	call Destroy
	
	cmp word[fireball_bool],1
	je d41
	mov word[movement],6
	call nextposition
	
	d41:
	jmp ExitNextPosition 
	
	d5:
	mov ah,[screen_attribute]
	mov al,' '
	mov [es:si],ax
	mov ah,[ballAtrribute]
	mov al,[ball]
	mov [es:di],ax
	mov [currentPosition],di
	jmp ExitNextPosition
	
	
nextcond3:
	cmp dx,5
	je awaen4
	jmp nextcond4

awaen4	
	mov di,si
	sub di,160
	sub di,2
	mov ah,[patterAttribute]
	mov al,' '
	
	cmp [es:di],ax
	jne e1
	
	push di
	call Destroy
	cmp word[fireball_bool],1
	je e11
	mov word[movement],6
	call nextposition
	e11:
	jmp ExitNextPosition 
	e1:
	mov ah,[screen_attribute]
	mov al,'-'
	cmp [es:di],ax
	jne e2
	mov word[movement],6
	call nextposition
	jmp ExitNextPosition 
	
	e2:
	mov ah,[screen_attribute]
	mov al,'|'
	cmp [es:di],ax
	jne e3
	mov word[movement],3
	call nextposition
	jmp ExitNextPosition 
	e3:
	mov bx,si
	sub bx,2
	cmp [es:bx],ax
	jne e4
	
	push bx
	call Destroy
	
	cmp word[fireball_bool],1
	je e31
	
	mov word[movement],3
	call nextposition
	e31:
	jmp ExitNextPosition 
	
	
	e4:
	mov ah,[screen_attribute]
	mov al,' '
	mov [es:si],ax
	mov ah,[ballAtrribute]
	mov al,[ball]
	mov [es:di],ax
	mov [currentPosition],di
	jmp ExitNextPosition

nextcond4:
	cmp dx,6
	je awaen1
	jmp ExitNextPosition
awaen1:	
	mov di,si
	add di,160
	sub di,2
	mov ah,[patterAttribute]
	mov al,' '
	
	cmp [es:di],ax
	jne f1
	
	push di
	call Destroy
	
	cmp word[fireball_bool],1
	je f11
	
	mov word[movement],5
	call nextposition
	
	f11:
	
	jmp ExitNextPosition 
	f1:
	mov ah,[screen_attribute]
	mov al,'|'
	cmp [es:di],ax
	jne f2
	mov word[movement],4
	call nextposition
	jmp ExitNextPosition 
	
	f2:
	mov ah,[screen_attribute]
	mov al,'-'
	cmp [es:di],ax
	jne f3
	call reduceLife
	call restart
	jmp ExitNextPosition
	
	f3:
	mov ah,[attribute]
	mov al,' '
	cmp [es:di],ax
	jne f4
	
	
	
	
	cmp di,[reflectorMid]
	ja f31
	jb f32
	mov word[movement],1
	jmp f33
	f31:
	mov word[movement],3
	jmp f33
	f32:
	mov word[movement],5
	jmp f33
	
	
	f33:
	
	
	call nextposition
	jmp ExitNextPosition
	
	
	f4:
	mov ah,[patterAttribute]
	mov al,' '
	
	cmp [es:si - 2],ax
	jne f5
	mov ax,si
	sub ax,2
	push ax
	call Destroy
	
	cmp word[fireball_bool],1
	je f51
	
	mov word[movement],4
	call nextposition
	
	f51:
	
	jmp ExitNextPosition 

	
	f5:
	mov ah,[screen_attribute]
	mov al,' '
	mov [es:si],ax
	mov ah,[ballAtrribute]
	mov al,[ball]
	mov [es:di],ax
	mov [currentPosition],di
	jmp ExitNextPosition


	
ExitNextPosition:	
	pop es
	pop di
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
	
	ret	


;<----------------------------- Clear Screen----------------------------->
;Clear Screen Print a specific attribute space

clrscr: 		push es
				push ax
				push cx
				push di
				mov ax, 0xb800
				mov es, ax ; point es to video base
				xor di, di ; point di to top left column
				mov ah,[screen_attribute]
				mov al, 0x20 ; space char in normal attribute
				mov cx, 2000 ; number of screen locations
				cld ; auto increment mode
				rep stosw ; clear the whole screen
				pop di
				pop cx
				pop ax
				pop es
				ret
;<----------------------------- Brick Pattern----------------------------->
;Prints Brick Pattern
				
BrickPattern:
	push ax
	push cx
	push di
	push es
	
	mov ax,0xb800
	mov es,ax
	
	mov ah,[patterAttribute]
	mov al,0x20
	
	mov di,[patternStart]
	mov cx,[noOfBricks]
	shr cx,1
	
	cld
	
PatterMaker1:
	push cx
	mov cx,[patternLength]
	rep stosw
	add di,10
	pop cx
	Loop PatterMaker1
	
	mov cx,[noOfBricks]
	shr cx,1
	
	mov di,[patternStart]
	add di,330
PatterMaker2:
	push cx
	mov cx,[patternLength]
	rep stosw
	add di,10
	pop cx
	Loop PatterMaker2

	
	pop es
	pop di
	pop cx
	pop ax
	
	ret
				
;<----------------------------- Border----------------------------->
;Prints border
				
border:
		push ax
		push bx
		push cx
		push es
		push di
		
		cld
		mov ax,0xb800
		mov es,ax
		
		mov ah,[screen_attribute]
		mov al,'-'
		
		mov di,160
		mov cx,80
		
		rep stosw
		
		mov cx,80
		mov di,3840
		
		rep stosw
		
		mov cx,24
		mov di,160
		mov al,'|'
leftmargin:
		mov [es:di],ax
		add di,160
		loop leftmargin
		
		
		mov cx,24
		mov di,318
rightmargin:
		mov [es:di],ax
		add di,160
		loop rightmargin
		
		
		
		pop di
		pop es
		pop cx
		pop bx
		pop ax
		
		ret

;<----------------------------- Create Bar----------------------------->
;Prints moving bar at the start of the game				
create:
	push cx
	push di
	push ax
	push es
		
	mov ax,0xb800
	mov es ,ax
	mov ah,[screen_attribute]
	mov al,' '
	mov di,3682
	mov cx,78
	cld
	rep stosw

	mov di,[reflectorStart]
	mov ah,[attribute]
	mov al,0x20
	mov cx,[reflectorEnd]
	sub cx,[reflectorStart]
	shr cx,1
	add cx,1
	cld
	rep stosw
	
	
	
	pop es
	pop ax
	pop di
	pop cx
	ret
;<----------------------------- Move Left----------------------------->
;Moves the bar towards left
	
moveleft:
			push ax
			push bx
			push cx
			push di
			push si
			push es
			push ds
			
			mov ax,0xb800
			mov es,ax
			
			mov di,[reflectorEnd]
			mov si,[reflectorStart]
			cmp si,3682
			jbe out1
			mov ah,[attribute]
			mov al,0x20
			mov bl,al
			mov bh,[screen_attribute]
			sub si,2
			mov [es:si],ax
			mov [es:di],bx
			mov [reflectorStart],si
			sub di,2
			mov [reflectorEnd],di
			
			sub word[reflectorMid],2
			
out1:			
			pop ds
			pop es
			pop si
			pop di
			pop cx
			pop bx
			pop ax
			ret
			
			
;<----------------------------- Move Right----------------------------->
;Moves the bar towards right			
			
moveright:
			push ax
			push bx
			push di
			push si
			push es
			
			
			mov ax,0xb800
			mov es,ax
			
			mov di,[reflectorEnd]
			mov si,[reflectorStart]
			
			cmp di,3836
			jae out2
			mov ah,[attribute]
			mov al,0x20
			mov bl,al
			mov bh,[screen_attribute]
			add di,2
			mov [es:si],bx
			mov [es:di],ax
			mov [reflectorEnd],di
			add si,2
			mov [reflectorStart],si
			
			add word[reflectorMid],2
			
out2:			
			pop es
			pop si
			pop di
			pop bx
			pop ax
			ret
;<----------------------------- FireBall Mover----------------------------->			
PowerFireBall:			
		push ax
		push es
		push si
		push di
			
		mov ax,0xb800
		mov es,ax
		
		mov si,[PowerPositions]
		mov ah,[screen_attribute]
		mov al,' '
		mov [es:si],ax
		
		
		mov di,si
		add di,160
		
		mov al,'-'
		cmp [es:di],ax
		jne FPowerc1
		mov word[PowerPositions],0
		mov word[Fireball_mov],0
		jmp ExitPowerFireBall

FPowerc1:
		mov al,' '
		cmp [es:di],ax
		jne FPowerc2
		mov al,[Powercharacter]
		mov word [PowerPositions],di
		mov [es:di],ax
		jmp ExitPowerFireBall

FPowerc2:
		mov ah,[attribute]
		mov al,' '
		cmp [es:di],ax
		jne ExitPowerFireBall
		mov word[Fireball_mov],0 
		mov al,[ballAtrribute]
		;and al,0xF0
		mov al,0x04
		mov [ballAtrribute],al
		mov word[fireball_bool],1

ExitPowerFireBall:		
		pop di
		pop si
		pop es
		pop ax
		
		ret 		
			
			
;<----------------------------- Power Mover----------------------------->			
PowerMover:			
		push ax
		push es
		push si
		push di
			
		mov ax,0xb800
		mov es,ax
		
		mov si,[PowerPositions]
		mov ah,[screen_attribute]
		mov al,' '
		mov [es:si],ax
		
		
		mov di,si
		add di,160
		
		mov al,'-'
		cmp [es:di],ax
		jne Powerc1
		mov word [PowerBool],0
		mov word[PowerPositions],0
		jmp ExitPowerMover
Powerc1:
		mov al,' '
		cmp [es:di],ax
		jne Powerc2
		mov al,[Powercharacter]
		mov word [PowerPositions],di
		mov [es:di],ax
		jmp ExitPowerMover

Powerc2:
		mov ah,[attribute]
		mov al,' '
		cmp [es:di],ax
		jne ExitPowerMover
		mov word[PowerBool],0
		mov word[PowerTimeBool],1
		mov word[PowerPositions],0
		mov byte[attribute],0x4F
		sub word[reflectorStart],4
		add word[reflectorEnd],4
		call create

ExitPowerMover:		
		pop di
		pop si
		pop es
		pop ax
		
		ret 		
			
;<----------------------------- KeyBoard ISR----------------------------->		
			
kbisr: 	push ax
		push bx
		push cx
		push dx
		
		push es		

		in al, 0x60 ; read a char from keyboard port
		
		cmp al, 0x4b ; is the key left shift
		jne cond1
		call moveleft

cond1:		
		cmp al,0x4d
		jne nomatch
		call moveright
		

nomatch: 
		pop es
		pop dx
		pop cx
		pop bx
		pop ax
		
		jmp far [cs:oldisr1] ; call the original ISR

;<----------------------------- Timer ISR----------------------------->
		
		
timer:
	push ax
	push bx
	push cx
	push dx
	
	push si
	push di

	push es
	cmp word[GameEnd],1
	jne awaen5

	;call PrintMessage
	jmp	quit_timer
	
awaen5:
	cmp word[power_delayer],6
	jne awaen2
	mov word[power_delayer],0
fireball:
	cmp word[Fireball_mov],1
	jne extension
	
	call PowerFireBall
	jmp awaen2
extension:
	cmp word[PowerBool],1
	jne awaen2
	
	call PowerMover
	
awaen2:	
	
	mov ax,[time_delayer]
	cmp ax,18
	;jne quit_timer
	jne PowerChecker
	mov word[time_delayer],0
	
	call Display

	
PowerChecker:
	cmp word[PowerTimer],546
	jne moveForward
	mov word[PowerTimeBool],0
	mov word[PowerTimer],0
	mov byte[attribute],0xFF
	add word[reflectorStart],4
	sub word[reflectorEnd],4
	call create
moveForward:	
	mov ax,[ball_delayer]
	cmp ax,[movfast]
	jne FireBallChecker
	mov word[ball_delayer],0
	jne quit_timer
	call nextposition
	
FireBallChecker:
	
	cmp word[fireball_timer],546
	jne quit_timer
	mov word[fireball_bool],0
	mov word[fireball_timer],0
	mov byte[ballAtrribute],0x0F
quit_timer:
	
	cmp word[fireball_bool],1
	jne extensionPower
	inc word[fireball_timer]
extensionPower:	
	cmp word[PowerTimeBool],1
	jne ptimercond
	inc word[PowerTimer]
ptimercond:	
	inc word[ball_delayer]
	inc word[time_delayer]
	inc word[power_delayer]
	pop es
	
	pop di
	pop si
	
	pop dx
	pop cx
	pop bx
	pop ax
	
	jmp far [cs:oldisr]
;<-----------------------------Sound----------------------------->
Sound:
	
		mov     al, 182         ; Prepare the speaker for the
        out     43h, al         ;  note.
        mov     ax, 4560        ; Frequency number (in decimal)
                                ;  for middle C.
        out     42h, al         ; Output low byte.
        mov     al, ah          ; Output high byte.
        out     42h, al 
        in      al, 61h         ; Turn on note (get value from
                                ;  port 61h).
        or      al, 00000011b   ; Set bits 1 and 0.
        out     61h, al         ; Send new value.
        mov     bx, 25          ; Pause for duration of note.
.pause1:
        mov     cx,25000
.pause2:
        dec     cx
        jne     .pause2
        dec     bx
        jne     .pause1
        in      al, 61h         ; Turn off note (get value from
                                ;  port 61h).
        and     al, 11111100b   ; Reset bits 1 and 0.
        out     61h, al         ; Send new value.

		RET
		
	
	
;<-----------------------------Beep----------------------------->
;creates beep sound

BEEP:
MOV     DX,2000          ; Number of times to repeat whole routine.

MOV     BX,1             ; Frequency value.

MOV     AL, 10110110B    ; The Magic Number (use this binary number only)
OUT     43H, AL          ; Send it to the initializing port 43H Timer 2.

NEXT_FREQUENCY:          ; This is were we will jump back to 2000 times.

MOV     AX, BX           ; Move our Frequency value into AX.

OUT     42H, AL          ; Send LSB to port 42H.
MOV     AL, AH           ; Move MSB into AL  
OUT     42H, AL          ; Send MSB to port 42H.

IN      AL, 61H          ; Get current value of port 61H.
OR      AL, 00000011B    ; OR AL to this value, forcing first two bits high.
OUT     61H, AL          ; Copy it to port 61H of the PPI Chip
                         ; to turn ON the speaker.

MOV     CX, 100          ; Repeat loop 100 times
DELAY_LOOP:              ; Here is where we loop back too.
LOOP    DELAY_LOOP       ; Jump repeatedly to DELAY_LOOP until CX = 0


INC     BX               ; Incrementing the value of BX lowers 
                         ; the frequency each time we repeat the
                         ; whole routine

DEC     DX               ; Decrement repeat routine count

CMP     DX, 0            ; Is DX (repeat count) = to 0
JNZ     NEXT_FREQUENCY   ; If not jump to NEXT_FREQUENCY
                         ; and do whole routine again.

                         ; Else DX = 0 time to turn speaker OFF

IN      AL,61H           ; Get current value of port 61H.
AND     AL,11111100B     ; AND AL to this value, forcing first two bits low.
OUT     61H,AL           ; Copy it to port 61H of the PPI Chip
                         ; to turn OFF the speaker.
ret	
		

		
;<----------------------------- Main ----------------------------->	
start:  

		call clrscr
		call border
		call create
		call BrickPattern
		
		xor ax, ax
		mov es, ax ; point es to IVT base
		
		mov ax, [es:8*4]
		mov [oldisr], ax ; save offset of old routine
		mov ax, [es:8*4+2]
		mov [oldisr+2], ax ; save segment of old routine
		
		mov ax, [es:9*4]
		mov [oldisr1], ax ; save offset of old routine
		mov ax, [es:9*4+2]
		mov [oldisr1+2], ax ; save segment of old routine
		
		cli ; disable interrupts
		mov word [es:9*4], kbisr ; store offset at n*4
		mov [es:9*4+2], cs ; store segment at n*4+2
		sti ; enable interrupts
		
		cli ; disable interrupts
		mov word [es:8*4], timer ; store offset at n*4
		mov [es:8*4+2], cs ; store segment at n*4+2
		sti ; enable interrupts

		
		mov ax,0xb800
		mov es,ax
		
		mov ah,[screen_attribute]
		mov al,[ball]
		
		mov di,[currentPosition]
			
		mov [es:di],ax	
		
l1:		 
		cmp word[GameEnd],1
		jne l1 ; if no, check for next key
		
		call PrintMessage

l2:		
		mov ah, 0 ; service 0 – get keystroke
		int 0x16 ; call BIOS keyboard service
		cmp al, 27 ; is the Esc key pressed
		jne l2
		
		cli ; disable interrupts
		mov ax,[oldisr1]
		mov word [es:9*4], ax ; store offset at n*4
		mov ax,[oldisr1+2]
		mov [es:9*4+2], ax ; store segment at n*4+2
		sti ; enable interrupts
		
		cli ; disable interrupts
		mov ax,[oldisr]
		mov word [es:8*4], ax ; store offset at n*4
		mov ax,[oldisr+2]
		mov [es:8*4+2], ax ; store segment at n*4+2
		sti ; enable interrupts
		
		mov byte[screen_attribute],0x07
		call clrscr

ExitMain:		
		mov ax, 0x4c00 ; terminate program
		int 0x21






