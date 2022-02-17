##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## .
##

# Compiler
CC = gcc

# Output names
LIBNAME = libmy_malloc.so

# Compiler flags
CFLAGS = -shared -g3 -I./include -fPIC -ldl

# Source
LIBSOURCE = malloc.c \
	free.c \
	calloc.c \
	realloc.c

# Objects
LIBOBJ = $(LIBSOURCE:.c=.o)

$(LIBNAME): $(LIBOBJ)
	gcc -o $(LIBNAME) $(LIBOBJ) $(CFLAGS)

all: $(LIBNAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(LIBNAME)

re: fclean all

.PHONY: re fclean clean re