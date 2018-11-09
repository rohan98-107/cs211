CC = gcc

all: sixth

sixth: sixth.c
	$(CC) -g -Wall -Werror -fsanitize=address -std=c99 sixth.c -o sixth

clean:
	rm -rf sixth