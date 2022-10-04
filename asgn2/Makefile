CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm


all: mathlib-test

mathlib-test: mathlib-test.o e.o euler.o madhava.o bbp.o viete.o newton.o
	$(CC) -o mathlib-test mathlib-test.o e.o euler.o madhava.o bbp.o viete.o newton.o $(LFLAGS)

mathlib-test.o: mathlib-test.c mathlib.h
	$(CC) $(CFLAGS) -c mathlib-test.c

e.o: e.c
	$(CC) $(CFLAGS) -c e.c

euler.o: euler.c
	$(CC) $(CFLAGS) -c euler.c

madhava.o: madhava.c
	$(CC) $(CFLAGS) -c madhava.c

bbp.o: bbp.c
	$(CC) $(CFLAGS) -c bbp.c

viete.o: viete.c
	$(CC) $(CFLAGS) -c viete.c

newton.o: newton.c
	$(CC) $(CFLAGS) -c newton.c

format:
	clang-format -i -style=file *.[ch]

clean:
	rm -f mathlib-test *.o
