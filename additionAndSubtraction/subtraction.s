SYSEXIT	= 1
EXIT_SUCCESS = 0
SYSCALL32 = 0x80

.code32

.data
number1:
    .long 0x11111111, 0x00000006, 0x00000004, 0x00000003
#	.long 0x00000002, 0x00000002, 0x00000002,0x00000002


liczba1_len = (.-number1)		
liczba1_cou = liczba1_len / 4

number2:
    .long 0x11111112, 0x00000007, 0x00000005, 0x00000004
#	.long 0x00000001, 0x00000001, 0x00000001,0x00000001

.bss

.text
.global _start
_start:
	pushl $0
	movl $0, %edi
	movl $0, %ebx
	movl $liczba1_cou, %edx

	loop_subb:
		clc 
		popf
		movl number1(,%edi,4), %eax
		sbbl number2(,%edi,4), %eax
		pushl %eax
		pushf 
		addl $1, %edi
		cmpl %edx, %edi
		jne loop_subb


	popl %eax
	andl $1, %eax
	jz no_collection
	xor %eax, %eax
	not %eax
    no_collection:
	pushl %eax

	mov $SYSEXIT, %eax
	mov $EXIT_SUCCESS, %ebx
	int $SYSCALL32
	

