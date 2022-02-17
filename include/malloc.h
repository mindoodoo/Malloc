/*
** EPITECH PROJECT, 2022
** malloc.h
** File description:
** malloc
*/

#ifndef MALLOC_H
#define MALLOC_H

#include <unistd.h>
#include <sys/types.h>

#define abs(x) ((x < 0) ? (x * -1) : (x))

#define header_offset(addr) (addr + 8)

#define next_block(addr, size) (addr + 8 + size)

extern size_t *first_block;

void *malloc(size_t size);
void free(void *ptr);

#endif