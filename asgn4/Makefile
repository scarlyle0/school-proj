CC = clang
CFLAGS = -g -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: tsp

tsp: tsp.o graph.o stack.o path.o
	$(CC) -o tsp tsp.o graph.o stack.o path.o $(LFLAGS)

tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

stack.o: stack.c
	 $(CC) $(CFLAGS) -c stack.c

path.o: path.c
	$(CC) $(CFLAGS) -c path.c

format:
	clang-format -i -style=file *.[ch]

clean:  
	rm -f tsp *.o

