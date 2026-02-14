.section .text
.global context_switch_to_user
.global context_save_kernel

/* Save kernel registers into cpu_state structure */
context_save_kernel:
    /* eax = pointer to cpu_state_t */
    pushad
    mov 36(%esp), %edx
    mov %esp, %ecx
    mov (%esp), %ebx
    mov %ebx, 0(%eax)
    mov 4(%esp), %ebx
    mov %ebx, 4(%eax)
    mov 8(%esp), %ebx
    mov %ebx, 8(%eax)
    mov 12(%esp), %ebx
    mov %ebx, 12(%eax)
    mov 16(%esp), %ebx
    mov %ebx, 16(%eax)
    mov 20(%esp), %ebx
    mov %ebx, 20(%eax)
    mov 24(%esp), %ebx
    mov %ebx, 24(%eax)
    mov 28(%esp), %ebx
    mov %ebx, 28(%eax)
    add $32, %esp
    popad
    ret

/* Restore CPU state and iret to user mode */
context_switch_to_user:
    /* eax = pointer to cpu_state_t */
    mov 0(%eax), %edi
    mov 4(%eax), %esi
    mov 8(%eax), %ebp
    mov 16(%eax), %ebx
    mov 20(%eax), %edx
    mov 24(%eax), %ecx
    
    /* Get eip, eflags, user_esp */
    mov 32(%eax), %edx   /* eip */
    mov 36(%eax), %ecx   /* eflags */
    mov 40(%eax), %eax   /* user_esp */
    
    /* Push iret frame */
    pushl $0x23          /* user SS */
    pushl %eax            /* user ESP */
    pushl %ecx           /* EFLAGS */
    pushl $0x1B          /* user CS */
    pushl %edx           /* EIP */
    
    mov 28(%eax), %eax   /* restore eax last */
    iret

