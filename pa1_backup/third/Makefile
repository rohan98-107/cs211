CC = gcc

all: third

third: third.c
	$(CC) -g -Wall -Werror -fsanitize=address -std=c99 third.c -o third

clean: 
	rm -rf third
