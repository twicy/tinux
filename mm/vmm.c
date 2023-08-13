#include "idt.h"
#include "string.h"
#include "debug.h"
#include <utils/vmm.h>
#include "pmm.h"

#define wd_to_addr(addr, val) \
	__asm__ volatile ("movl %0, [%1];\n":: "a"(addr), "b"(val))

static void setup_pd() {
	int i, j;
	pde_t first_pde;
	pde_t second_pde;

	memset((void *)PAGE_DIR_START_PHYS, 0, PAGE_DIR_ENTRY * sizeof(pde_t));
	// setup pde[0] and pde[768]
	first_pde = PAGE_TABLE_START_PHYS | PAGE_PRESENT | PAGE_WRITE;
	// setup pde[769]
	second_pde = PAGE_DIR_START_PHYS | PAGE_PRESENT | PAGE_WRITE;

	wd_to_addr(PAGE_DIR_START_PHYS, first_pde);
	wd_to_addr(PAGE_DIR_START_PHYS + PGD_INDEX(PAGE_OFFSET) * sizeof(pde_t),
		first_pde);

	wd_to_addr(PAGE_DIR_START_PHYS + (PGD_INDEX(PAGE_OFFSET) + 1) * sizeof(pde_t),
		second_pde);

	for (i = (PGD_INDEX(PAGE_OFFSET) + 2), j = 2; i < PAGE_DIR_ENTRY; i++, j++) {
		wd_to_addr(PAGE_DIR_START_PHYS + i * sizeof(pde_t),
			PAGE_TABLE_START_PHYS + j * PAGE_SIZE);
	}
}

static void setup_pt() {
	int i;
	pte_t tmp;

	// map the first 1M, virt[0M, 1M] to phys[0M, 1M], storing from phys[1M, 1M + 4K]
	// This is where pde[0] and pde[768] points to
	for (i = 0; i < 256; i++) {
		tmp = (i << PAGE_SHIFT) | PAGE_PRESENT | PAGE_WRITE;
		wd_to_addr(PAGE_TABLE_START_PHYS + 0 * sizeof(pte_t), tmp);
	}
}


void enable_paging() {
	setup_pd();
	setup_pt();

	uint32_t esp;
	asm volatile ("mov [%%esp], %0" : "=r"(esp));
	esp += 0xc0000000;
	asm volatile ("mov %0, [%%esp]" : : "r"(esp));

	// setup temp page dir
	asm volatile ("mov %0, %%cr3" : : "r" (PAGE_DIR_START_PHYS));
	// setup PE bit for cr0 register
	uint32_t cr0;

	asm volatile ("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= 0x80000000;
	asm volatile ("mov %0, %%cr0" : : "r" (cr0));

}
