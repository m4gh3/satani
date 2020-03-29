CFLAGS=-g

example_calculator: build/parse.o build/tape.o
	$(CC) $(CFLAGS) build/parse.o build/tape.o examples/calculator.c -o calculator

clean:
	rm build/*.o

clean_examples:
	rm calculator

build/parse.o: build/tape.o src/parse.c
	$(CC) $(CFLAGS) build/tape.o src/parse.c -c -o build/parse.o

build/tape.o: src/tape.c
	$(CC) $(CFLAGS) src/tape.c -c -o build/tape.o

