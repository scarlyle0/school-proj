CC = clang
CFLAGS = -g -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: banhammer

banhammer: banhammer.o bv.o bf.o speck.o node.o bst.o ht.o parser.o
	$(CC) -o banhammer banhammer.o bv.o bf.o speck.o node.o bst.o ht.o parser.o $(LFLAGS)

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bst.o: bst.c
	$(CC) $(CFLAGS) -c bst.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

format:
	clang-format -i -style=file *.[ch]

clean:
	rm -f banhammer *.o
