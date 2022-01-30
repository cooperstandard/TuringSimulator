build:
	gcc turing.c -o turing.o


makeT:
	gcc turing.c -o turing.o
	./turing.o 1000

clean:
	rm turing.o
