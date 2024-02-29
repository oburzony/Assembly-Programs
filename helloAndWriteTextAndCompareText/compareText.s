
SYSCALL32 = 0x80
SYSEXIT = 1
EXIT_SUCCESS = 0
SYSWRITE = 4
STDOUT = 1
SYSREAD = 3
STDIN = 0	

.data
buf: .ascii "     "
buf_len = . - buf

.text
msg: .ascii "Write text (5): \n"
msg_len = . - msg

msg2: .ascii "Yes - same string of characters"
msg2_len = . - msg2

msg3: .ascii "No - different string of characters"
msg3_len = . - msg3

equal: .ascii "equal"
equal_len = . - equal

newline: .ascii "\n"
newline_len = . - newline
	    
.global _start

_start:
	mov $SYSWRITE, %eax
    mov $STDOUT, %ebx
	mov $msg, %ecx
	mov $msg_len, %edx
	int $SYSCALL32

    mov $SYSREAD, %eax
    mov $STDIN, %ebx
	mov $buf, %ecx
	mov $buf_len, %edx
	int $SYSCALL32

    mov $buf, %ebx
	mov $buf_len, %ecx
    mov $equal, %edx

compare:
    cmp $0, %ecx
    je ending1
    mov (%ebx), %al
    cmp %al, (%edx)
    jne ending2
    inc %ebx
    inc %edx
    dec %ecx
    jmp compare

ending1:
    mov $SYSWRITE, %eax
    mov $STDOUT, %ebx
	mov $msg2, %ecx
	mov $msg2_len, %edx
	int $SYSCALL32
    jmp exit

ending2:
    mov $SYSWRITE, %eax
    mov $STDOUT, %ebx
	mov $msg3, %ecx
	mov $msg3_len, %edx
	int $SYSCALL32
    jmp exit

exit:
    mov $SYSWRITE, %eax
    mov $STDOUT, %ebx
	mov $newline, %ecx
	mov $newline_len, %edx
	int $SYSCALL32

	mov $SYSEXIT, %eax
	mov $EXIT_SUCCESS, %ebx
    int $SYSCALL32


