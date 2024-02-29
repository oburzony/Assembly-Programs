all:addition subtraction 

addition: addition.o
		ld -m elf_i386 addition.o -o addition

addition.o: addition.s
		as --32 --gstabs addition.s -o addition.o

subtraction: subtraction.o
		ld -m elf_i386 subtraction.o -o subtraction

subtraction.o: subtraction.s
		as --32 --gstabs subtraction.s -o subtraction.o
	
