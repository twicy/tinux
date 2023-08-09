#include "console.h"
#include "printk.h"
#include "gdt.h"
#include "idt.h"
#include "debug.h"

int kern_entry()
{
	init_debug();
	init_gdt();
	init_idt();

	clear_console();
	console_print_str("111 22 33 44\n", rc_black, rc_brown);
	// panic("test");
	asm volatile ("int $0x3");
	asm volatile ("int $0x4");
	return 0;
}
