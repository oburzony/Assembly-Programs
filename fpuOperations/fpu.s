SYSEXIT = 1
EXIT_SUCCESS = 0
SYSCALL32 = 0x80

.data
    value1: 
        .float 4.1
    value2: 
        .float -2.9
    value0: 
        .float 0.0 
    value5: 
        .double 5.4     
    sn:
        .long 0b0000000001111111
    sd:
        .long 0b0000010001111111
    su:
        .long 0b0000100001111111
    dtz:
        .long 0b0000111001111111
    dn:
        .long 0b0000001001111111
    en:
        .long 0b0000001101111111                         

.bss
    .lcomm controlWord, 2        
.text

.global _start
_start:

finit   
fstcw   controlWord

nan:
    flds value0
    flds value0
    fdivr %st(0), %st(1) 
    fstp %st(0)

zerom:
    flds value2
    flds value0
    fmul %st(0), %st(1) 
    fstp %st(0)

zerop:  
    flds value1
    flds value0
    fmul %st(0), %st(1) 
    fstp %st(0)

infm:
    flds value2
    flds value0
    fdivr %st(0), %st(1) 
    fstp %st(0)

infp:
    flds value1
    flds value0
    fdivr %st(0), %st(1) 
    fstp %st(0)

stopop:
    finit
jmp addop
    
addop:
    flds value1
    flds value2
    fadd %st(0), %st(1) 
    fstp %st(0)
    jmp subbop

subbop:
    flds value1
    flds value2
    fsubr %st(0), %st(1) 
    fstp %st(0)
    jmp mulop

mulop:
    flds value1
    flds value2
    fmul %st(0), %st(1) 
    fstp %st(0)
    jmp divop

divop:
    flds value1
    flds value2
    fdivr %st(0), %st(1) 
    fstp %st(0) 
    jmp setsn
    
setsn:
    finit
    fldcw sn
    jmp setsd
setsd:
    finit
    fldcw sd
    jmp setsu
setsu:
    finit
    fldcw su
    jmp setdtz
setdtz:
    finit
    fldcw dtz
    jmp setdn
setdn:
    finit
    fldcw dn
    jmp seten
seten:
    finit
    fldcw en
    jmp end
end:
fldcw controlWord
finit
movl $SYSEXIT, %eax
movl $EXIT_SUCCESS, %ebx
int  $SYSCALL32
