[org 0x0100]


num1_ms: dd 10101010h
num1_ls: dd 10101010h


shl word [num1_ls],1
rcl word [num1_ls+2],1

rcl word [num1_ms],1
rcl word [num1_ms+2],1




mov ax, 0x4c00
int 21h