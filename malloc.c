/*
** EPITECH PROJECT, 2022
** malloc.c
** File description:
** .
*/

#include "include/malloc.h"

void *first_block = NULL;

void *first_alloc(size_t size)
{
    block_header_t *output = sbrk(0);
    size_t alloc_size = size + sizeof(block_header_t);
    int n2_pages = (alloc_size % (4096 * 2)) + 1;

    sbrk(n2_pages * 4096 * 2);
    output->size = alloc_size;
    output->next = NULL;
    first_block = output;

    return output + sizeof(block_header_t);
}

void *find_free(block_header_t *start, size_t size)
{
    block_header_t *head = start;
    block_header_t *best_fit = NULL;

    while (head) {
        if (head->isFree && abs(best_fit->size - size) > abs(head->size - size))
            best_fit = head;
        head = head->next;
    }
    return best_fit;
}

void *create_block(size_t size)
{
    block_header_t *end = first_block;
    block_header_t *output;

    while (end->next) end = end->next;
    if ((void *)(end + sizeof(block_header_t) + end->size) > sbrk(0))
        sbrk(((size + sizeof(block_header_t)) % (4096 * 2) + 1) * (4096 * 2)); // Inch'allah
    output = end + end->size + sizeof(block_header_t);
    end->next = output;
    output->isFree = 0;
    output->size = size;
    output->next = NULL;

    return output + sizeof(block_header_t);
}

void *malloc(size_t size)
{
    block_header_t *target = NULL;

    if (!size)
        return NULL;
    if (!first_block)
        return first_alloc(size);
    else {
        target = find_free(first_block, size + sizeof(block_header_t));
        if (!target)
            return create_block(size);
        else {
            target->isFree = 0;
            return target + sizeof(block_header_t);
        }
    }
}