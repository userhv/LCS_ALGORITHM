#
# Copyright 2021 Helio Victor Flexa dos Santos - Federal University of Minas Gerais
#

# c and flags
CC = gcc
CFLAGS = -std=c11 -g -Wall
#CFLAGS = -std=c++11 -O3 -Wall

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/

# all sources, objs, and header files
MAIN = Main
TARGET = run.out
SRC = $(wildcard $(SRC_FOLDER)*.c)
OBJ = $(patsubst $(SRC_FOLDER)%.c, $(OBJ_FOLDER)%.o, $(SRC))

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes --track-fds=yes $(BIN_FOLDER)$(TARGET)

clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)*

