/*
** EPITECH PROJECT, 2022
** realloc.c
** File description:
** .
*/

#include <string.h>
#include "include/malloc.h"

void *realloc(void *ptr, size_t size)
{
    void *new = NULL;
    size_t current_size;

    if (!ptr)
        return malloc(size);
    new = malloc(size);
    current_size = (*(size_t*)(ptr - 8)) ^ 1;
    memcpy(new, ptr, current_size);
    free(ptr);
    return new;
}