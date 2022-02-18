/*
** EPITECH PROJECT, 2022
** calloc.c
** File description:
** .
*/

#include "include/malloc.h"

void *calloc(size_t nmemb, size_t size)
{
    size_t alloc_size = nmemb * size;
    char *output = malloc(alloc_size);

    for (int i = 0; i < alloc_size; i++)
        output[i] = 0;
    return output;
}