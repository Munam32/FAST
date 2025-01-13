[org 0x0100]

mov bx, 1011000110001001b

mov ax, 1010101110100101b
mov dx,16
mov cx,0 

count: 
    shr bx,1
    jnc skip

inc cx

skip:
    dec dx 
    jz complement
    jmp count

complement: 
    mov dx,0

l1:
    cmp bx,cx
    rcl dx,1
    dec cx
    jnz l1

xor ax,dx


mov ax,0x4c00
int 21h
