CC = gcc
CFLAGS = -std=c99 -Wall -g

Q1_DIR = q1-counting-inversions

all: q1

# q1/utils.o
$(Q1_DIR)/utils.o: $(Q1_DIR)/utils.c $(Q1_DIR)/utils.h 
	$(CC) $(CFLAGS) -c $(Q1_DIR)/utils.c -o $(Q1_DIR)/utils.o

# q1 binary
q1: $(Q1_DIR)/main.c $(Q1_DIR)/utils.o 
	$(CC) $(CFLAGS) $(Q1_DIR)/main.c $(Q1_DIR)/utils.o -o q1

run-test1: q1
	./q1

run-test-vg1: q1
	valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes ./q1

clean:
	rm -f $(Q1_DIR)/*.o q1