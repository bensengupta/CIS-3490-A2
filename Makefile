CC = gcc
CFLAGS = -std=c99 -Wall -g

P1_DIR = P1
P2_DIR = P2

all: problem1 problem2

# utils/utils.o
utils/utils.o: utils/utils.c utils/utils.h 
	$(CC) $(CFLAGS) -c utils/utils.c -o utils/utils.o

# P1/P1utils.o
$(P1_DIR)/P1utils.o: $(P1_DIR)/P1utils.c $(P1_DIR)/P1utils.h 
	$(CC) $(CFLAGS) -c $(P1_DIR)/P1utils.c -o $(P1_DIR)/P1utils.o

# P2/P2utils.o
$(P2_DIR)/P2utils.o: $(P2_DIR)/P2utils.c $(P2_DIR)/P2utils.h 
	$(CC) $(CFLAGS) -c $(P2_DIR)/P2utils.c -o $(P2_DIR)/P2utils.o

# problem1 binary
problem1: $(P1_DIR)/P1.c $(P1_DIR)/P1utils.o utils/utils.o
	$(CC) $(CFLAGS) $(P1_DIR)/P1.c $(P1_DIR)/P1utils.o utils/utils.o -o problem1

# problem2 binary
problem2: $(P2_DIR)/P2.c $(P2_DIR)/P2utils.o utils/utils.o
	$(CC) $(CFLAGS) $(P2_DIR)/P2.c $(P2_DIR)/P2utils.o utils/utils.o -o problem2

run-test1: problem1
	./problem1

run-test2: problem2
	./problem2

run-test-vg1: problem1
	valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes ./problem1

run-test-vg2: problem2
	valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes ./problem2

clean:
	rm -f $(P1_DIR)/*.o $(P2_DIR)/*.o utils/*.o problem1 problem2