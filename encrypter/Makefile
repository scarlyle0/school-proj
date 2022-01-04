CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic $(shell pkg-config --cflags gmp)
LFLAGS = -lm $(shell pkg-config --libs gmp)

all: keygen encrypt decrypt

encrypt: encrypt.o numtheory.o randstate.o rsa.o
	$(CC) -o encrypt encrypt.o numtheory.o randstate.o rsa.o $(LFLAGS)

decrypt: decrypt.o numtheory.o randstate.o rsa.o
	$(CC) -o decrypt decrypt.o numtheory.o randstate.o rsa.o $(LFLAGS)

keygen: keygen.o numtheory.o randstate.o rsa.o
	$(CC) -o keygen keygen.o numtheory.o randstate.o rsa.o $(LFLAGS)

encrypt.o: encrypt.c
	$(CC) $(CFLAGS) -c encrypt.c

decrypt.o: decrypt.c
	$(CC) $(CFLAGS) -c decrypt.c

rsa.o: rsa.c
	$(CC) $(CFLAGS) -c rsa.c

keygen.o: keygen.c
	$(CC) $(CFLAGS) -c keygen.c

numtheory.o: numtheory.c
	$(CC) $(CFLAGS) -c numtheory.c

randstate.o: randstate.c
	$(CC) $(CFLAGS) -c randstate.c

format:
	clang-format -i -style=file *.[ch]

clean:
	rm -f keygen *.o
	rm -f encrypt *.o
	rm -f decrypt *.o
