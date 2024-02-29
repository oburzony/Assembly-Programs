SYSCALL32 = 0x80
SYSEXIT = 1
EXIT_SUCCESS = 0
SYSWRITE = 4
STDOUT = 1

.text
msg: .ascii "Hello! \n"
msg_len = . - msg

.global _start
_start:
	mov $SYSWRITE, %eax
    	mov $STDOUT, %ebx
	mov $msg, %ecx
	mov $msg_len, %edx
	int $SYSCALL32

	mov $SYSEXIT, %eax
	mov $EXIT_SUCCESS, %ebx
    int $SYSCALL32


