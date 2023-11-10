CC = gcc.exe
CFLAGS = -Wall -g
MAKEFILE_PATH := $(realpath $(lastword $(MAKEFILE_LIST)))
SRC_DIR = $(shell powershell -Command "& {Split-Path -Path '$(MAKEFILE_PATH)' -Parent}")
OBJ_DIR = obj/Debug
BIN_DIR = bin/Debug

SOURCE_FILES = $(wildcard $(SRC_DIR)/*.c)

OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCE_FILES))

EXECUTABLE = $(BIN_DIR)/Projeto_Duda_Doces_Facilitada.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(OBJ_DIR)\*.o
	del $(EXECUTABLE)