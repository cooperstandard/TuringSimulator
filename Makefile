build: turing.o
	gcc turing.c -o turing.o


makeT: turing.o
	gcc turing.c -o turing.o
	./turing.o 1000 0
	make clean

clean:
	rm turing.o
