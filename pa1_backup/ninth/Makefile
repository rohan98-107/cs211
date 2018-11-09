CC = gcc

all: ninth

ninth: ninth.c
	$(CC) -g -Wall -Werror -fsanitize=address -std=c99 ninth.c -o ninth

clean:
	rm -rf ninth