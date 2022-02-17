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

    return malloc(alloc_size);
}