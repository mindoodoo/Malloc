##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## .
##

# Compiler
CC = gcc

# Output names
TESTBIN = bin
LIBNAME = libmy_malloc.so

# Compiler flags
LIBFLAGS = -shared -g3 -I./include
TESTFLAGS = -Wall -g3 -I./include

# Source
LIBSOURCE = malloc.c
TESTSOURCE = main.c

# Objects
LIBOBJ = $(LIBSOURCE:.c=.o)
TESTOBJ = $(TESTSOURCE:.c=.o)

$(LIBNAME): $(LIBOBJ)
	$(CC) -o $(LIBNAME) $(LIBOBJ) $(LIBFLAGS)

$(TESTBIN): $(TESTOBJ)
	$(CC) -o $(TESTBIN) $(TESTOBJ) $(TESTFLAGS)

all: $(LIBNAME) $(TESTBIN)

clean:
	rm -f *.o

fclean: clean
	rm -f $(LIBNAME) $(TESTBIN)

re: fclean all

.PHONY: re fclean clean re