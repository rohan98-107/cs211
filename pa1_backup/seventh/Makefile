CC = gcc

all: seventh

seventh: seventh.c
	$(CC) -g -Wall -Werror -fsanitize=address -std=c99 seventh.c -o seventh

clean:
	rm -rf seventh