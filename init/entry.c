#include "console.h"
#include "printk.h"

int kern_entry()
{
	clear_console();
	char *str1 = "Hello\n";
	// char *str2 = "123";
	printk("%s123", str1);
	console_print_str("111 22 33 44\n1", rc_black, rc_brown);

	return 0;
}
