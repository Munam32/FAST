[org 0x0100]
mov ax, 25h

jnz l1

Num: dw 12,25,38,44,105



l1:
mov ax,[0x105+bx]
add bx,2
add ax, [0x105+bx]
add bx,2
add ax, [0x105+bx]
add bx,2
add ax, [0x105+bx]
add bx,2
add ax, [0x105+bx]





mov bx, 10h

shl ax,1
shr bx,1

mov dx,1234h

mov [0x270],dx ; use braces always at he end when acessing ra address









mov ax, 0x4c00
int 0x21