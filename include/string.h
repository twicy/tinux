#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_
#include "types.h"

void *memcpy(void *dest, const void *src, size_t len);
void *memset(void *src, int val, size_t len);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
size_t strlen(const char *str);
#endif