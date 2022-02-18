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
    size_t allocated_size = (size / 8 + 1) * 8; // Respect 8B allignment (2 words)

    first_block = sbrk(0); // Get break location before breaking
    increase_heap(allocated_size);
    *first_block = allocated_size;
    *first_block |= 1;
    *(size_t *)next_block(first_block, allocated_size) = 0; // Mark stopper
    *(size_t *)next_block(first_block, allocated_size) |= 1; // Mark stopper as allocated
    return first_block + 8; // Return pointer to allocated memory (taking into account header offset)
}

void *best_fit(size_t size)
{
    void *pgm_break = sbrk(0);
    size_t *pointer = first_block;
    size_t *head = first_block;

    while (1) {
        if (*head ^ 1 == 0 && (*head & 1)) // Check if stopper (size 0 and last bit set)
            return NULL; // NOTE: Should try to understand bitwise operations better and improve hacky conditions
        if ((void *)head >= pgm_break)
            return NULL;
        if (*head ^ 1 < size) // Check if block size is at least equal to size
            continue;
        if (abs((*head ^ 1) - size) < abs((*pointer ^ 1) - size))
            pointer = head;
        head = next_block(head, ((*head) ^ 1));
    }
    return NULL;
}

void *alloc_block(size_t size)
{
    size_t allocated_size = (size / 8 + 1) * 8;
    void *pgm_break = sbrk(0);
    size_t *head = first_block;

    // Find next block
    while (1) {
        if (*head ^ 1 == 0 && (*head & 1)) // Check if stopper (size 0 and last bit set)
            break;
        if ((void *)head >= pgm_break) {
            head = NULL;
            break;
        }
        head = next_block(head, ((*head) ^ 1));
    }
    if ((void *)(head + allocated_size) > pgm_break)
        increase_heap(allocated_size); // Inneficiency here
    *head = allocated_size;
    *head |= 1;
    *(size_t *)(next_block(head, allocated_size)) = 1; // Same as =0 and |=1
    return head;
}

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