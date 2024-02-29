all: hello writeText compareText

hello: hello.o
	ld -s -o hello hello.o

hello.o: hello.s
	as hello.s -o hello.o

writeText: writeText.o
	ld -s -o writeText writeText.o

writeText.o: writeText.s
	as writeText.s -o writeText.o

compareText: compareText.o
	ld -s -o compareText compareText.o

compareText.o: compareText.s
	as compareText.s -o compareText.o

clean: hello hello.o writeText writeText.o compareText compareText.o
	rm hello hello.o
	rm writeText writeText.o
	rm compareText compareText.o
