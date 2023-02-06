CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

SRC = src
INC = include
OBJ = objects
BIN = bin

all: $(BIN)/P11 $(BIN)/P12 $(BIN)/P21 $(BIN)/P22 

release: CFLAGS += -O2
release: clean all

debug: CFLAGS += -g
debug: clean all

# obj/utils.o
$(OBJ)/utils.o: $(SRC)/utils.c $(INC)/utils.h 
	$(CC) $(CFLAGS) -c $(SRC)/utils.c -o $(OBJ)/utils.o
# obj/P1utils.o
$(OBJ)/P1utils.o: $(SRC)/P1utils.c $(INC)/P1utils.h 
	$(CC) $(CFLAGS) -c $(SRC)/P1utils.c -o $(OBJ)/P1utils.o
# obj/P2utils.o
$(OBJ)/P2utils.o: $(SRC)/P2utils.c $(INC)/P2utils.h 
	$(CC) $(CFLAGS) -c $(SRC)/P2utils.c -o $(OBJ)/P2utils.o

# bin/P11
$(BIN)/P11: $(SRC)/P11.c $(OBJ)/P1utils.o $(OBJ)/utils.o
	$(CC) $(CFLAGS) $(SRC)/P11.c $(OBJ)/P1utils.o $(OBJ)/utils.o -o $(BIN)/P11
# bin/P12
$(BIN)/P12: $(SRC)/P12.c $(OBJ)/P1utils.o $(OBJ)/utils.o
	$(CC) $(CFLAGS) $(SRC)/P12.c $(OBJ)/P1utils.o $(OBJ)/utils.o -o $(BIN)/P12
# bin/P21
$(BIN)/P21: $(SRC)/P21.c $(OBJ)/P2utils.o $(OBJ)/utils.o
	$(CC) $(CFLAGS) $(SRC)/P21.c $(OBJ)/P2utils.o $(OBJ)/utils.o -o $(BIN)/P21 -lm
# bin/P22
$(BIN)/P22: $(SRC)/P22.c $(OBJ)/P2utils.o $(OBJ)/utils.o
	$(CC) $(CFLAGS) $(SRC)/P22.c $(OBJ)/P2utils.o $(OBJ)/utils.o -o $(BIN)/P22 -lm

# valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BIN)/P11

clean:
	rm -f $(OBJ)/*.o $(BIN)/*