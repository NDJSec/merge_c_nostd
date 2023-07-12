CC=gcc
CFLAGS=-O0 -nostdlib -g -Wall -Werror -Wpedantic

SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

BINDIR=bin
BIN=bin/main

all:$(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(BINDIR)/* $(OBJ)/* merge/OCRModels merge/TranslationModels

clean_merge:
	$(RM) -rf merge/OCRModels merge/TranslationModels