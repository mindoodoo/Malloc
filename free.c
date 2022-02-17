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
    // NOTE : Coalescing should be implemented with the previous block too
    // To do so, implemented similar size / allocated header at bottom
}

void shrink_heap(size_t *ptr) {
    size_t *next = next_block(ptr, *ptr);
    void *pgm_break = sbrk(0);
    size_t size_to_break;

    if (!(*next) && (*next & 1)) { // Check if next is stopper
        size_to_break = pgm_break - (void *)ptr;
        if (size_to_break >= (2 * 4096)) // Check if at least two pages until break
            sbrk(-((size_to_break / (4096 * 2)) * 4086 * 2));
    }
}

void free(void *ptr)
{
    if (*(size_t*)ptr & 1) { // Check last bit
        *(size_t *)ptr ^= 1; // Clear last bit
        coalesce_next(ptr);
        // Don't forget to coalesce previous
        shrink_heap(ptr);
    }
}