; Kernel Entry Point
; Bootloader loads this code in 32-bit mode
; The program is waiting for loading at 0x1000
bits 16

section .text

global _start ; For linker

; Entry point
_start:
    ; Load GDT
    cli
    lgdt  [gdt_descriptor]

    ; Show the processor that it is in protected mode
    mov   eax, cr0
    or    al, 1
    mov   cr0, eax

    ; Far jump into kernel call function
    jmp   codesegment:call_kernel

gdt_start:
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start
    dw 0
;    Code segment
gdt_code:
    dw 0xFFFF     ; Limit. Full memory range
    dw 0          ; Base (low)
    db 0          ; Base (medium)
    db 10011010b  ; Flags. Executable bit = 1 because this is the code segment
    db 11001111b  ; Flags. Upper limit
    db 0          ; Base (high)

;    Data segment
gdt_data:
    dw 0xFFFF
    dw 0
    db 0
    db 10010010b  ; executable bit = 0 because this is the data segment
    db 11001111b
    db 0
gdt_end:


codesegment equ gdt_code - gdt_start
datasegment equ gdt_data - gdt_start

; This is where the jump is made after loading the GDT. Processor is in 32-bit mode
bits 32

extern kernel_main ; Kernel main function (void). Define in kernel.c

call_kernel:
    mov ax, datasegment
    mov ds, ax,
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call kernel_main
    jmp $