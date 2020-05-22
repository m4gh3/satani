CFLAGS=-g

example_calculator: build/parse.o build/tape.o
	$(CC) $(CFLAGS) build/parse.o build/tape.o examples/calculator.c -lm -o calculator

clean:
	rm build/*.o

clean_examples:
	rm calculator

build/libuparse.so: build/tape.o src/parse.o
	$(CC) $(CFLAGS) build/tape.o build/parse.o -shared -o build/libuparse.so

build/parse.o: build/tape.o build/parse.c
	$(CC) $(CFLAGS) build/tape.o src/parse.c -c -o build/parse.o

build/tape.o: src/tape.c
	$(CC) $(CFLAGS) src/tape.c -c -o build/tape.o

