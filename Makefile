CC = gcc
CFLAGS = -std=c99 -Wall -g

A2: A2.c
	$(CC) $(CFLAGS) A2.c -o A2

run-test: A2
	./A2

run-test-vg: A2
	valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes ./A2