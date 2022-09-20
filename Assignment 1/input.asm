global main
extern printf, scanf


section .data
    msgs: db "Enter a string: ",0
    msgi: db "Enter a number (Integer): ",0
    msgos: db "The string you have entered is: ",0
    msgoi: db "The number you have entered is: ",0
    integ: db "%d",0
    integout: db  "%d",10,0
    strng: db "%s",0
    strngout: db "%s",10,0
    stringvar times 100 db 0


section .text
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16


    xor eax,eax
    lea rdi, [msgi]
    call printf


    mov eax, 0
    lea rdi, [integ]
    lea rsi, [num]
    call scanf

    xor eax,eax
    lea rdi, [msgs]
    call printf

    mov eax, 0
    lea rdi, [strng]
    lea rsi, [stringvar]
    call scanf

    xor eax, eax
    lea rdi, [msgoi] 
    call printf

    xor eax, eax
    lea rdi, [integout]
    mov edx, [num] 
    call printf

    ; xor eax, eax
    ; lea rdi, [msgnl] 
    ; call printf

    xor eax, eax
    lea rdi, [msgos]
    call printf
    
    xor eax, eax
    lea rdi, [strngout]
    lea rsi, [stringvar]
    call printf

    ; xor eax, eax
    ; lea rdi, [msgnl] 
    ; call printf

    add rsp, 16
    leave
    ret


section .bss
    num resb 4
