CC = clang
CFLAGS = -g -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: encode decode

encode: encode.o huffman.o io.o node.o stack.o code.o pq.o
	$(CC) -o encode huffman.o encode.o node.o stack.o code.o io.o pq.o $(LFLAGS)

decode: decode.o huffman.o io.o node.o stack.o code.o pq.o
	$(CC) -o decode  huffman.o decode.o node.o stack.o code.o io.o pq.o $(LFLAGS)

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

code.o: code.c
	$(CC) $(CFLAGS) -c code.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

format:
	clang-format -i -style=file *.[ch]

clean:  
	rm -f encode *.o  
	rm -f decode *.o

