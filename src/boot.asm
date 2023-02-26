; Bootloader
; BIOS boots in 16-bit mode
; The program is waiting for loading at 0x7c00
bits 16
org 0x7c00

section .text

; Entry point
_start:
    ; Loading kernel
    mov bx, 0x1000    ; offset. The kernel is loaded at this address
    mov ah, 0x02      ; Int 13h/AH=2 = Read Sectors From Drive
    mov al, 0x07      ; Sectors to read
    mov ch, 0x00      ; cylinder
    mov cl, 0x02      ; Sector to read (start)
    mov dh, 0x00      ; Head

    int 13h

    popf
    jmp 0x0:0x1000


; Bringing the file to a size of 510 bytes
times 510-($-$$) db 0
; Boot signature
; On boot BIOS reads the last 2 bytes of the first sector, if it is 0xAA55 it loads it
dw 0xAA55