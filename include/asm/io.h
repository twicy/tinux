#include "types.h"

#define outb(port, value) \
__asm__ ("outb %%al, %%dx":: "a"(value), "d"(port))

#define inb(port, value) \
__asm__ ("inb %%al, %%dx":: "a"(value), "d"(port))

#define inw(port) ({ \
uint16_t ret; \
__asm__ volatile ("inw %%al, %%dx" : "=a" (ret) : "d" (port)); \
ret; \
})

