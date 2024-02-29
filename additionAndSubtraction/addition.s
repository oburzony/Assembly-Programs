SYSEXIT	= 1
EXIT_SUCCESS = 0
SYSCALL32 = 0x80

.code32

.data
number1:
	.long 0x11111111, 0x00000006, 0x00000004, 0x00000003
#	.long 0x00000001, 0x00000001, 0x00000001,0x00000001


number1_len = (.-number1)		
number1_cou = number1_len / 4

number2:
	.long 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
#	.long 0x00000001, 0x00000001, 0x00000001, 0x00000001

.bss

.text
.global _start

_start:
	pushl $0
	movl $0, %edi
	movl $number1_cou, %edx

	loop_add:
		clc 
		popf
		movl number1(,%edi,4), %eax
		adcl number2(,%edi,4), %eax
		pushl %eax
		pushf 
		addl $1, %edi
		cmpl %edx, %edi
		jne loop_add

	popl %eax
	andl $1, %eax
	pushl %eax
	
	mov $SYSEXIT, %eax
	mov $EXIT_SUCCESS, %ebx
	int $SYSCALL32

    

