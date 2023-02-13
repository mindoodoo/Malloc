# Malloc Re-implementation

This project is a basic reimplementation of the malloc family of standard library functions. This is done by **only** using the ```brk``` and ```sbrk``` system calls.

This project was done in **march 2022** over a period of **3 weeks.**

## Building

This project is built into a static library named ```libmy_malloc.so``` using make.

```
make
```

*or*

```
make re
```

## Usage

The following functions are implemented :

```
void *malloc(size_t size);
```

```
void *calloc(size_t nmemb, size_t size);
```

```
void *realloc(void *ptr, size_t size);
```

```
void free(void *ptr);
```

In order to use them, link your binary to the ```libmy_malloc.so``` static library. The function prototypes can be found in the ```include/malloc.h``` header file.

## Features

- **Full** memory alignment on a power of 2 bytes
- Allocation done in multiples of **2 pages**
- Utilizes **best fit** algorithm