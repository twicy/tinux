#include "console.h"
#include "printk.h"
#include "gdt.h"

int kern_entry()
{
	init_gdt();
	clear_console();
	console_print_str("111 22 33 44\n", rc_black, rc_brown);

	return 0;
}
