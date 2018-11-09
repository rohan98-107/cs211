CC = gcc

all: eighth

eighth: eighth.c
	$(CC) -g -Wall -Werror -fsanitize=address -std=c99 eighth.c -o eighth

clean:
	rm -rf eighth