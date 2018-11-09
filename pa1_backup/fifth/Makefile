CC = gcc

all: fifth

fifth: fifth.c
	$(CC) -g -Wall -Werror -fsanitize=address -std=c99 fifth.c -o fifth

clean:
	rm -rf fifth
