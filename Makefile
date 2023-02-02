CC = gcc
CFLAGS = -std=c99 -Wall -g

P1_DIR = P1

all: problem1

# P1/P1utils.o
$(P1_DIR)/P1utils.o: $(P1_DIR)/P1utils.c $(P1_DIR)/P1utils.h 
	$(CC) $(CFLAGS) -c $(P1_DIR)/P1utils.c -o $(P1_DIR)/P1utils.o

# problem1 binary
problem1: $(P1_DIR)/P1.c $(P1_DIR)/P1utils.o 
	$(CC) $(CFLAGS) $(P1_DIR)/P1.c $(P1_DIR)/P1utils.o -o problem1

run-test1: problem1
	echo "data_A2_Q1.txt\nd" | ./problem1

run-test-vg1: problem1
	valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes ./problem1

clean:
	rm -f $(P1_DIR)/*.o problem1