CC = clang
CFLAGS = -g -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: sorting

sorting: sorting.o insert.o stats.o shell.o heap.o quick.o	
	$(CC) -o sorting sorting.o insert.o stats.o shell.o heap.o quick.o $(LFLAGS)

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

stats.o: stats.c
	$(CC) $(CFLAGS) -c stats.c

insert.o: insert.c
	$(CC) $(CFLAGS) -c insert.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

format:
	clang-format -i -style=file *.[ch]

clean:	
	rm -f sorting *.o
