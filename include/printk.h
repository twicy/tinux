#ifndef INCLUDE_PRINTK_H_
#define INCLUDE_PRINTK_H_

#include "vargs.h"
#include "types.h"

#define BUF_MAX_LEN 1024

int printk(const char *format, ...);

#endif