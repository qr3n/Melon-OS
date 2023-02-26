bits 32

_start:
    int 30h    ; system call
    mov eax, 0 ; return 0
    ret
