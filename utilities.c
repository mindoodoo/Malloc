/*
** EPITECH PROJECT, 2022
** utilities.c
** File description:
** utilities
*/

#include "malloc.h"

void *next_block(void *addr, size_t size)
{
    return addr + 8 + size;
}