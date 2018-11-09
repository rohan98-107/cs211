CC = gcc

all: fourth

fourth: fourth.c
	$(CC) -g -Wall -Werror -fsanitize=address -std=c99 fourth.c -o fourth

clean:
	rm -rf fourth
