; [org 0x0100]

; jmp start

; clrscr:
;     pusha
    
;     push 0xb800
;     pop es

;     mov ax,0x720
;     xor di,di
;     mov cx,4000
    
;     rep stosw

;     popa

;     ret

; falling_Star:
;     push bp
;     mov bp,sp
;     pusha

    
;     xor bx,bx

;     mov al,80
;     mul bx
;     add ax,[bp+4]
;     shl ax,1
;     mov di,ax

;     push 0xb800
;     pop es
    

; l1:
;     sub di,160
;     mov word [es:di], 0x0720
;     add di,160
;     mov word [es:di], 0x7020
;     add di,160
;     mov cx,50000
; l2:
;     loop l2
;     mov cx,50000
; l3:
;     loop l3
;     cmp di,3840
;     jg reset
;     loop l1






; reset:
;     sub di,160
;     mov word [es:di], 0x0720
;     mov cx,24
; l4:
;     sub di,160
;     loop l4
;     jmp l1

;     popa
;     pop bp
;     ret 2





; start:
;     push 70
;     call clrscr
;     call falling_Star
;     mov ax,0x4c00
;     int 21h            




[org 0x0100]
jmp start
; PCB layout:
; ax,bx,cx,dx,si,di,bp,sp,ip,cs,ds,ss,es,flags,next,dummy
; 0, 2, 4, 6, 8,10,12,14,16,18,20,22,24, 26 , 28 , 30
pcb: times 4*16 dw 0 ; space for 32 PCBs
stack: times 4*256 dw 0 ; space for 32 512 byte stacks
nextpcb: dw 1 ; index of next free pcb
current: dw 0 ; index of current pcb
line: dw 79; line number for next thread

tickcount: dw 0

clrscr:
pusha
mov ax, 0xb800
mov es, ax
mov di, 0
nextchar: mov word [es:di], 0x7020
add di, 2
cmp di, 4000
jne nextchar
popa
ret
		delay:
pusha
mov cx,0xFFFF
delay_1:
loop delay_1
mov cx,0xFFFF
delay_2:
loop delay_2
mov cx,0xFFFF
delay_3:
loop delay_3
popa
ret
fallingstar:
push bp
mov bp,sp

mov di,[bp+4]
shl di,2

mov ax,0xb800
mov es,ax
mov cx,0
fallingstar_1:
mov word[es:di],0x702A
add di,160
call delay
call clrscr
add cx,1
cmp cx,25
jl fallingstar_1
mov di,[bp+4]
shl di,2
mov cx,0
jmp fallingstar_1

pop bp
ret 2
; subroutine to register a new thread
; takes the segment, offset, of the thread routine and a parameter
; for the target thread subroutine
		initpcb:
push bp
mov bp, sp
push ax
push bx
push cx
push si
mov bx, [nextpcb] ; read next available pcb index
cmp bx, 4 ; are all PCBs used
je exit
mov cl, 5
shl bx, cl ; multiply by 32 for pcb start
mov ax, [bp+8] ; read segment parameter
mov [pcb+bx+18], ax ; save in pcb space for cs

mov ax, [bp+6] ; read offset parameter
mov [pcb+bx+16], ax ; save in pcb space for ip
mov [pcb+bx+22], ds ; set stack to our segment
mov si, [nextpcb] ; read this pcb index
mov cl, 9
shl si, cl ; multiply by 512
add si, 256*2+stack ; end of stack for this thread
mov ax, [bp+4] ; read parameter for subroutine
sub si, 2 ; decrement thread stack pointer
mov [si], ax ; pushing param on thread stack
sub si, 2 ; space for return address
mov [pcb+bx+14], si ; save si in pcb space for sp
mov word [pcb+bx+26], 0x0200 ; initialize thread flags
mov ax, [pcb+28] ; read next of 0th thread in ax
mov [pcb+bx+28], ax ; set as next of new thread
mov ax, [nextpcb] ; read new thread index
mov [pcb+28], ax ; set as next of 0th thread
inc word [nextpcb] ; this pcb is now used
exit: pop si
pop cx
pop bx
pop ax
pop bp
ret 6
; timer interrupt service routine
timer: push ds
push bx
push cs
pop ds ; initialize ds to data segment
mov bx, [current] ; read index of current in bx
shl bx, 5
;shl bx, 1
mov [pcb+bx+0], ax ; save ax in current pcb
mov [pcb+bx+4], cx ; save cx in current pcb
mov [pcb+bx+6], dx ; save dx in current pcb
mov [pcb+bx+8], si ; save si in current pcb
mov [pcb+bx+10], di ; save di in current pcb
mov [pcb+bx+12], bp ; save bp in current pcb
mov [pcb+bx+24], es ; save es in current pcb
pop ax ; read original bx from stack

mov [pcb+bx+2], ax ; save bx in current pcb
pop ax ; read original ds from stack
mov [pcb+bx+20], ax ; save ds in current pcb
pop ax ; read original ip from stack
mov [pcb+bx+16], ax ; save ip in current pcb
pop ax ; read original cs from stack
mov [pcb+bx+18], ax ; save cs in current pcb
pop ax ; read original flags from stack
mov [pcb+bx+26], ax ; save cs in current pcb
mov [pcb+bx+22], ss ; save ss in current pcb
mov [pcb+bx+14], sp ; save sp in current pcb
mov bx, [pcb+bx+28] ; read next pcb of this pcb
mov [current], bx ; update current to new pcb
mov cl, 5
shl bx, cl ; multiply by 32 for pcb start
mov cx, [pcb+bx+4] ; read cx of new process
mov dx, [pcb+bx+6] ; read dx of new process
mov si, [pcb+bx+8] ; read si of new process
mov di, [pcb+bx+10] ; read diof new process
mov bp, [pcb+bx+12] ; read bp of new process
mov es, [pcb+bx+24] ; read es of new process
mov ss, [pcb+bx+22] ; read ss of new process
mov sp, [pcb+bx+14] ; read sp of new process
push word [pcb+bx+26] ; push flags of new process
push word [pcb+bx+18] ; push cs of new process
push word [pcb+bx+16] ; push ip of new process
push word [pcb+bx+20] ; push ds of new process
mov al, 0x20
out 0x20, al ; send EOI to PIC
mov ax, [pcb+bx+0] ; read ax of new process
mov bx, [pcb+bx+2] ; read bx of new process
pop ds ; read ds of new process
iret ; return to new process


start:
call clrscr
xor ax, ax
mov es, ax ; point es to IVT base
cli
mov word [es:8*4], timer
mov [es:8*4+2], cs ; hook timer interrupt

sti

nextkey:
xor ah, ah ; service 0 – get keystroke
int 0x16 ; bios keyboard services
cmp al,'8'
jne nextkey
push cs ; use current code segment
mov ax, fallingstar
push ax ; use mytask as offset
push word [line] ; thread parameter
call initpcb ; register the thread
sub word [line],5 ; update line number
jmp nextkey ; wait for next keypress