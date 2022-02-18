/*
** EPITECH PROJECT, 2022
** free.c
** File description:
** .
*/

#include "include/malloc.h"

void coalesce_next(size_t *ptr)
{
    size_t *next = next_block(ptr, *ptr);

    if (!(*next & 1))
        *ptr += 8 + *next;
}

void shrink_heap(size_t *ptr) {
    size_t *next = next_block(ptr, *ptr);
    void *pgm_break = sbrk(0);
    size_t size_to_break;

    if (!(*next) && (*next & 1)) {
        size_to_break = pgm_break - (void *)ptr;
        if (size_to_break >= (2 * 4096))
            sbrk(-((size_to_break / (4096 * 2)) * 4086 * 2));
    }
}

void free(void *ptr)
{
    if (!ptr)
        return;
    ptr -= 8;
    if (*(size_t*)ptr & 1) {
        *(size_t *)ptr ^= 1;
        coalesce_next(ptr);
        shrink_heap(ptr);
    }
}