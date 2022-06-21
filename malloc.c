/*
** EPITECH PROJECT, 2022
** malloc.c
** File description:
** .
*/

#include <stdio.h>
#include "include/malloc.h"

size_t *first_block = NULL;

// Increases size of the heap by multiples of two pages
void increase_heap(size_t size)
{
    size_t n_pages = (size / (4096 * 2)) * 2 + 2;
    
    sbrk(n_pages * 4096);
}

// Initializes malloc linked list
// Does initial increase of program break
void *init_malloc(size_t size)
{
    size_t allocated_size = (size / 8 + 1) * 8;

    first_block = sbrk(0);
    increase_heap(allocated_size);
    *first_block = allocated_size;                              // Set size in block header
    *first_block |= 1;                                          // Mark block as used

    *(size_t *)next_block(first_block, allocated_size) = 0;     // Mark last block
    *(size_t *)next_block(first_block, allocated_size) |= 1;

    return first_block + 8;                                     // Return first_block with header offset
}

// Tries to find closest fit in previously allocated blocks
void *best_fit(size_t size)
{
    void *pgm_break = sbrk(0);
    size_t *alloc = first_block;
    size_t *head = first_block;

    while (1) {
        if (*head ^ 1 == 0 && (*head & 1))                      // If stopper, ret NULL
            return NULL;
        if ((void *)head >= pgm_break)
            return NULL;
        if (*head ^ 1 < size)
            continue;   // NOTE: Needs to be tested, this seems like it would create
                        // an infinite loop by forgoing next_block()
        if (!(*head & 1) && abs((*head ^ 1) - size) < abs((*alloc ^ 1) - size))
            alloc = head;
        head = next_block(head, ((*head) ^ 1));
    }

    // If block is not allocated, mark allocated and return addr + header offset
    if (!(*alloc & 1)) {
        *alloc |= 1;
        return (alloc + 8);
    }
    
    return NULL;
}

// Create new block when no preexisting blocks found
void *alloc_block(size_t size)
{
    size_t allocated_size = (size / 8 + 1) * 8;
    void *pgm_break = sbrk(0);
    size_t *head = first_block;

    // Loop until header of last block
    while (1) {
        if (*head ^ 1 == 0 && (*head & 1))                      // If stopper
            break;
        if ((void *)head >= pgm_break) {
            head = NULL;    // NOTE: This is not handled, and will cause a crash
            break;
        }
        head = next_block(head, ((*head) ^ 1));
    }

    if ((void *)(head + allocated_size) > pgm_break)
        increase_heap(allocated_size);
    *head = allocated_size;
    *head |= 1;
    *(size_t *)(next_block(head, allocated_size)) = 1;
    return (head + 8);
}

// Main malloc function
void *malloc(size_t size)
{
    void *output = NULL;

    if (!size)
        return NULL;
    if (!first_block)
        return init_malloc(size);
    else {
        output = best_fit(size);
        if (!output)
            output = alloc_block(size);
    }
    return output;
}