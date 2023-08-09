#include "string.h"
#include "types.h"

void *memcpy(void *dest, const void *src, size_t len) {
    uint8_t *s = (uint8_t *)src;
    const uint8_t *d = (uint8_t *)dest;
    
    for (; len != 0; len--) {
        *s++=*d++;
    }
    return dest;
}

void *memset(void *src, int val, size_t len) {
    uint8_t *s = (uint8_t *)src;
    unsigned char *c = (unsigned char *)&val;

    for (; len != 0; len--) {
        *s++ = *c;
    }
    return src;
}

char *strcpy(char *dest, const char *src) {
    char *d = dest;

    while (*src != '\0') {
        *d++ = *src++;
    }

    *d = '\0';
    return dest;
}

char *strcat(char *dest, const char *src) {
    char *d_end = dest;
    while (*d_end != '\0') {
        d_end++;
    }
    while (*src != '\0') {
        *d_end++ = *src++;
    }

    *d_end = '\0';
    return dest;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

size_t strlen(const char *src)
{
	const char *eos = src;

        while (*eos++)
	      ;

	return (eos - src - 1);
}

void bzero(void *dest, size_t len)
{
	memset(dest, 0, len);
}