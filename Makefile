CC=gcc
CFLAGS=-I. -Wall -Wextra -Werror -std=c99 -pedantic -O2
DEPS = campanha.hpp
OBJ = campanha.o main.o 

all: main run

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: 
	./main < input.txt

clean:
	rm -f *.o main