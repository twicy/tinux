

#ifndef INCLUDE_VMM_H
#define INCLUDE_VMM_H

#include "types.h"
#include "idt.h"
#include <utils/vmm.h>

#define PAGE_SHIFT          12
#define PAGE_TABLE_SHIFT    10
#define PAGE_DIR_SHIFT      10
#define PAGE_OFFSET 	    0xC0000000
#define PAGE_PRESENT        0x1
#define PAGE_WRITE 	        0x2
#define PAGE_USER 	        0x4
#define PAGE_SIZE 	        (1 << PAGE_SHIFT)
#define PAGE_MASK           ~0xFFF

#define PGD_INDEX(x) (((x) >> (PAGE_SHIFT + PAGE_TABLE_SHIFT)) & 0x3FF)
#define PTE_INDEX(x) (((x) >> PAGE_SHIFT) & 0x3FF)
#define OFFSET_INDEX(x) ((x) & 0xFFF)

typedef uint32_t pde_t;
typedef uint32_t pte_t;

#define PAGE_DIR_ENTRY      (1 << PAGE_DIR_SHIFT)
#define PAGE_TABLE_ENTRY    (1 << PAGE_TABLE_SHIFT)

#define PAGE_DIR_START_PHYS     (0x100000 + PAGE_SIZE)
#define PAGE_TABLE_START_PHYS   0x10000

void enable_paging();
#endif 	// INCLUDE_VMM_H
