#include "console.h"
#include <asm/io.h>

/*
	VGA text mode framebuffer:
	manipulate a 80 * 25 array of 16-bit values that starts from VGA_TEXT_BUF_START
	control what show up on the console by directly writing into that buffer

	each 2 bytes <==> a char on the screen
	the first byte:
		first 4 bits defines the background colour
			actually the first bit is BLINK
		last 4 bits defines the foreground colour
			actually the first bit is BLINK
		when you blink, the colour is shallowed!
	the second byte is the ascii of the char
*/

static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;
static uint16_t *vga_text_buf = (uint16_t *)VGA_TEXT_BUF_START;

static uint8_t setup_colour_attr(uint8_t foreground, uint8_t background) {
	return (background << 4) | (foreground & 0x0F);
}

static void update_cursor() {
	uint16_t cursor_location;
	
	cursor_location = cursor_y * COLUMN_MAX + cursor_x;
	outb(VGA_CTRL_REGISTER, 14); // sending upper 8 bits
	outb(VGA_DATA_REGISTER, cursor_location >> 8);
	outb(VGA_CTRL_REGISTER, 15); // sending lower 8 bits
	outb(VGA_DATA_REGISTER, cursor_location);
}

static void scroll() {
	int i;
	uint8_t attr;
	uint16_t blank;
	
	attr = setup_colour_attr(rc_black, rc_white);
	blank = SPACE_ASCII | (attr << 8);

	if (cursor_y < ROW_MAX) {
		return;
	}

	for (i = 0; i < (ROW_MAX - 1) * COLUMN_MAX; i++) {
		vga_text_buf[i] = vga_text_buf[i + COLUMN_MAX];
	}
	for (i = (ROW_MAX - 1) * COLUMN_MAX; i < ROW_MAX * COLUMN_MAX; i++) {
		vga_text_buf[i] = blank;
	}

	cursor_y = ROW_MAX - 1;
	update_cursor();
}

void clear_console() {
	int i;
	uint8_t attr;
	uint16_t blank;
	
	attr = setup_colour_attr(rc_black, rc_white);
	blank = SPACE_ASCII | (attr << 8);

	for (i = 0; i < ROW_MAX * COLUMN_MAX; i++) {
		vga_text_buf[i] = blank;
	}

	cursor_x = 0;
	cursor_y = 0;
	update_cursor();
}

static void console_print_char(char c, uint8_t foreground, uint8_t background) {
	uint8_t attr;
	
	attr = setup_colour_attr(foreground, background);
	switch (c)
	{
	case BACKSPACE_ASCII:
		if (cursor_x == 0) {
			cursor_x = COLUMN_MAX - 1;
			if (cursor_y != 0) {
				cursor_y--;
			}
		} else {
			cursor_x--;
		}
		break;

	case TAB_ASCII:
		cursor_x = (cursor_x + 8) & ~7;
		break;

	case '\r':
		cursor_x = 0;
		break;
	case '\n':
		cursor_x = 0;
		cursor_y++;
		break;

	default:
		vga_text_buf[cursor_y * COLUMN_MAX + cursor_x] = c | (attr << 8);
		cursor_x++;
		break;
	}

	if (cursor_x >= COLUMN_MAX) {
		cursor_x = 0;
		cursor_y++;
	}
	scroll();
	update_cursor();
}

void console_print_str(char *str, uint8_t foreground, uint8_t background) {
	while (*str != '\0') {
		console_print_char(*str, foreground, background);
		str++;
	}
}