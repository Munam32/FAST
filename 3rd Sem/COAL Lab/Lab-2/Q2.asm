[org 0x0100]



mov ax, 200h
mov bx, 250h

mov dx,25h
mov [0x0200],dx
mov dx,15h
mov [0x0250],dx


mov ax,[bx+0]
mov cx,[250h]

mov [0x0200],ax
mov [0x0250],dx


mov ax,[num1+12]
mov bx,[num1+0]
mov [num1+0],ax
mov [num1+12],bx ; -1,1,0,0,1,3,2

mov ax,[num1+4]
mov bx,[num1+2]
mov [num1+2],ax
mov [num1+4],bx ; -1,0,1,0,1,3,2

mov ax,[num1+6]
mov bx,[num1+4]
mov [num1+4],ax
mov [num1+6],bx ; -1,0,0,1,1,3,2

mov ax,[num1+10]
mov bx,[num1+12]
mov [num1+10],ax
mov [num1+12],bx


mov ax, 0x4c00
int 21h

num1: dw 2,1,0,0,1,3,-1