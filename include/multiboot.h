#ifndef INCLUDE_MULTIBOOT_H_
#define INCLUDE_MULTIBOOT_H_

#include "types.h"
// recap, in boot.s : mov [glb_mboot_ptr], ebx
// Reference: multiboot spc
typedef
struct multiboot_t {
	// flags indicate whether the followings are present
	// e.g. mem_lower is present if flags[0] is set
	uint32_t flags;
	// measured in KB
	// lower memory starts at address 0
	uint32_t mem_lower;
	// upper memory starts at 1M
	uint32_t mem_upper;

	uint32_t boot_device;
	uint32_t cmdline;
	uint32_t mods_count;
	uint32_t mods_addr;
	// the following indicate where the section header table from an ELF kernel is
	// size of each entry, number of entries, and the string table used as indexes of names
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;
	// the address and length of a buffer containing a memory map of the machine
	uint32_t mmap_length;		
	uint32_t mmap_addr;
	
	uint32_t drives_length;
	uint32_t drives_addr;
	uint32_t config_table;
	uint32_t boot_loader_name;
	uint32_t apm_table;
	uint32_t vbe_control_info;
	uint32_t vbe_mode_info;
	uint32_t vbe_mode;
	uint32_t vbe_interface_seg;
	uint32_t vbe_interface_off;
	uint32_t vbe_interface_len;
} __attribute__((packed)) multiboot_t;

typedef
struct mmap_entry_t {
	// size of the associated structure in bytes
	uint32_t size;
	// the starting address
	uint32_t base_addr_low;
	uint32_t base_addr_high;
	// the size of memory region in bytes
	uint32_t length_low;
	uint32_t length_high;
	// 1=>RAM, 3=>ACPI info, and so on
	uint32_t type;
} __attribute__((packed)) mmap_entry_t;

extern multiboot_t *glb_mboot_ptr;

#endif 	// INCLUDE_MULTIBOOT_H_
