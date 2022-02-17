/*
** EPITECH PROJECT, 2022
** malloc.c
** File description:
** .
*/

#include <stdio.h>
#include "include/malloc.h"

size_t *first_block = NULL;

void increase_heap(size_t size)
{
    size_t n_pages = (size / (4096 * 2)) * 2 + 2; // Time two because divided by PAGE_SIZE * 2,
    // +2 for "surplus"
    sbrk(n_pages * 4096);
}

void *init_malloc(size_t size)
{
    size_t allocated_size = size / 8 + 1; // Respect 8B allignment (2 words)

    first_block = sbrk(0); // Get break location before breaking
    allocated_size *= 8;
    increase_heap(allocated_size);
    *first_block = allocated_size;
    *first_block |= 1;
    *next_block(first_block, allocated_size) = 0; // Mark stopper
    *next_block(first_block, allocated_size) |= 1; // Mark stopper as allocated
    return header_offset(first_block); // Return pointer to allocated memory
}

void *best_fit()
{
    size_t *pointer;
    size_t *head = first_block;
     *((size_t*)first_block) + (*((size_t*)first_block) & 1); // Round up bitwise

    while (1) {
        if (*head == 0 && (*head & (1 << 1))) { // Check if stopper
            return NULL;
        }
    }

    return NULL;
}

void *malloc(size_t size)
{
    void *output = NULL;

    if (!size)
        return NULL;
    if (!first_block)
        return init_malloc(size);
    else {
        printf("Nothing.");
    }
}