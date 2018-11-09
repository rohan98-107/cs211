CC = gcc

all: second

second: second.c
	$(CC) -Wall -Werror -fsanitize=address -std=c99 second.c -o second

clean: 
	rm -rf second
