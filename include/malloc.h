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

typedef struct block_header_s {
    void *next;
    int isFree;
    size_t size;
} block_header_t;

extern void *first_block;

void *malloc(size_t size);
void free(void *ptr);

#endif