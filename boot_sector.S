; Simple boot sector for OS-Mini-Ai
; This bootsector loads the kernel from disk and jumps to it

.code16
.globl _start
_start:
    xor %ax, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss
    
    ; Set stack at 0x0000:0x7C00
    mov $0x7C00, %sp
    
    ; Load kernel from disk
    mov $0x02, %ah        ; BIOS read sector function
    mov $0x00, %ch        ; Cylinder 0
    mov $0x01, %cl        ; Sector 1 (skip boot sector)
    mov $0x00, %dh        ; Head 0
    mov $0x00, %dl        ; Drive 0 (floppy)
    mov $0x10, %ax        ; Number of sectors to read (16)
    mov $0x1000, %bx      ; Buffer to load to (0x1000)
    int $0x13
    jc disk_error
    
    ; Jump to kernel at 0x1000:0000
    jmp 0x1000:0x0000

disk_error:
    mov $0x00, %ah
    int $0x16            ; Wait for keypress
    int $0x19            ; Reboot

    .fill 510-(.-_start), 0, 0
    .word 0xAA55        ; Boot signature

