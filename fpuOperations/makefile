all:fpu

fpu: fpu.o
		ld -m elf_i386 fpu.o -o fpu

fpu.o: fpu.s
		as --32 --gstabs fpu.s -o fpu.o

