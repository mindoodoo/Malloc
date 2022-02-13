/*
** EPITECH PROJECT, 2022
** free.c
** File description:
** .
*/

#include "include/malloc.h"

void free(void *ptr)
{
    block_header_t *header = (block_header_t*)ptr - sizeof(block_header_t);

    header->isFree = 1;
    header->size = 0;
}