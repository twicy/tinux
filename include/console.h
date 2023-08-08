#ifndef INCLUDE_CONSOLE_H_
#define INCLUDE_CONSOLE_H_

#include "types.h"

#define VGA_TEXT_BUF_START 0xB8000
#define VGA_TEXT_BUF_END 0xBFFFF
#define VGA_CTRL_REGISTER 0x3D4
#define VGA_DATA_REGISTER 0x3D5
#define COLUMN_MAX 80
#define ROW_MAX 25

#define SPACE_ASCII 0x20
#define TAB_ASCII 0x08
#define BACKSPACE_ASCII 0x09


typedef
enum real_color {
	rc_black,
	rc_blue,
	rc_green,
	rc_cyan,
	rc_red,
	rc_magenta,
	rc_brown,
	rc_light_grey,
	rc_dark_grey,
	rc_light_blue,
	rc_light_green,
	rc_light_cyan,
	rc_light_red,
	rc_light_magenta,
	rc_light_brown, 	// yellow
	rc_white
} real_color_t;

void clear_console();
void console_print_str(char *str, uint8_t foreground, uint8_t background);

#endif  // INCLUDE_CONSOLE_H_
