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

extern size_t *first_block;

void *next_block(void *addr, size_t size);

void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

#endif