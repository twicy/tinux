#include "console.h"
#include "printk.h"
#include "gdt.h"
#include "idt.h"
#include "debug.h"
#include "timer.h"
#include "pmm.h"

int kern_entry()
{
	init_debug();
	init_gdt();
	init_idt();

	clear_console();
	printk("Hello, OOOS kernelllllll!\n");

	init_timer(200);

	// asm volatile ("int $0x3");
	// asm volatile ("int $0x21");
	// asm volatile ("int $0x20");
	// asm volatile ("sti");

	printk("kernel in memory start: 0x%08X\n", kern_start);
	printk("kernel in memory end:   0x%08X\n", kern_end);
	printk("kernel in memory used:   %d KB\n\n", (kern_end - kern_start) / 1024);
	
	show_memory_map();

	return 0;
}
