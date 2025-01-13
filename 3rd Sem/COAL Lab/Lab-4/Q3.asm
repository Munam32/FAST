[org 0x100]
jmp start
multiplicandLSD: dd 0xABCDD4E1
multiplicandHSD: dd 0h
multiplier: dd 0xAB5C32
RLSD: dd 0b
RHSD: dd 0b

start: mov cx, 32

checkbit: shr word[multiplier+2], 1
  
rcr word[multiplier], 1
jnc skip
mov ax, [multiplicandLSD]
add word[RLSD], ax
mov ax,[multiplicandLSD+2]
adc word[RLSD+2],ax
mov ax,[multiplicandHSD]
adc word[RHSD],ax
mov ax,[multiplicandHSD+2]
adc word[RHSD+2],ax

skip: shl word[multiplicandLSD],1
rcl word[multiplicandLSD+2], 1
rcl word[multiplicandHSD], 1
rcl word[multiplicandHSD+2], 1
sub cx, 1
jnz checkbit

mov ax,0x4c00
int 21h