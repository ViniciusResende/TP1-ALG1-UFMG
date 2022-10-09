CC=gcc
CFLAGS=-I. -Wall -Wextra -Werror -std=c99 -pedantic -O2
DEPS = campanha.hpp
OBJ = campanha.o main.o 
TARGET = tp01

all: main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLAGS)

run: 
	./tp01 < casoTeste01.txt

clean:
	rm -f *.o tp01