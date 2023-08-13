#include "console.h"
#include "string.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "pmm.h"
#include <utils/vmm.h>
#include <utils/kernel.h>

void kern_init()
{
	// init_debug();
	// init_gdt();
	// init_idt();
	enable_paging();
	clear_console();
	printk("Hello, OSSSSSSSSSS kernel!\n");

	// init_timer(200);

	// // 开启中断
	// // asm volatile ("sti");

	// printk("kernel in memory start: 0x%08X\n", kern_start);
	// printk("kernel in memory end:   0x%08X\n", kern_end);
	// printk("kernel in memory used:   %d KB\n\n", (kern_end - kern_start) / 1024);
	
	// show_memory_map();
	// init_pmm();

	// printk("\nThe Count of Physical Memory Page is: %u\n\n", phy_page_count);

	// uint32_t allc_addr = NULL;
	// printk("Test Physical Memory Alloc :\n");
	// allc_addr = pmm_alloc_page();
	// printk("Alloc Physical Addr: 0x%08X\n", allc_addr);
	// allc_addr = pmm_alloc_page();
	// printk("Alloc Physical Addr: 0x%08X\n", allc_addr);
	// allc_addr = pmm_alloc_page();
	// printk("Alloc Physical Addr: 0x%08X\n", allc_addr);
	// allc_addr = pmm_alloc_page();
	// printk("Alloc Physical Addr: 0x%08X\n", allc_addr);

	while (1) {
		asm volatile ("hlt");
	}
}

