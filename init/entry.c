#include "console.h"
#include "printk.h"
#include "gdt.h"
#include "idt.h"
#include "debug.h"
#include "timer.h"

int kern_entry()
{
	init_debug();
	init_gdt();
	init_idt();

	clear_console();
	printk("Hello, OS kernel!\n");

	init_timer(200);

	// asm volatile ("int $0x3");
	// asm volatile ("int $0x21");
	// asm volatile ("int $0x20");
	asm volatile ("sti");

	return 0;
}
