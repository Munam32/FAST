[org 0x0100]

jmp start

clrscr:
    mov ax,0xb800
    mov es,ax
    mov di,0
    mov ax, 0x0720
    mov cx, 2000
    cld
    REP stosw
    
    ret


printnum:
    push bp
    mov bp,sp
    mov ax,0xb800
    mov es,ax
    mov ax,[bp+4]
    mov bx,10
    mov cx,0

nextdigit:
    mov dx,0
    div bx
    add dl,0x30
    push dx
    inc cx
    cmp ax,0
    jnz nextdigit
    mov di,160

nextpos:
    pop dx
    mov dh,0x07
    mov [es:di],dx
    add di,2
    loop nextpos

    pop bp
    ret 2


start:
    call clrscr

    in al, 0x21
    xor ah,ah
    
    push ax
    call printnum 

    mov ax,0x4c00
    int 21h