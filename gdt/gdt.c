#include "gdt.h"
#include "string.h"

// (kernel, user mode) X (code segment, data segment)
// and a NULL entry
#define GDT_LENGTH 5

gdt_entry_t gdt_entries[GDT_LENGTH];

gdt_ptr_t gdt_ptr;

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

extern uint32_t stack;

// Reference: Intel 64 and IA-32 Architectures
// Software Developer's Manual, Volume 3A, P98 and P100
void init_gdt()
{
	gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH - 1;
	gdt_ptr.base = (uint32_t)&gdt_entries;

    // the 5 segments are: NULL, kernel code segment, kernel data segment
    // user space code segment, userspace data segment
	gdt_set_gate(0, 0, 0, 0, 0);
    // 0xCF = 0b 1100 1111
	// 0x9A = 0b 1|00|1|1010
    // the above means:
    /* 
        1 => P = 1, the segment is preset in memory
        00 => DPL = 0, kernel mode
        1 => S = 1, this is code/data segment; and not a system segment
        1010 => Descriptor Type: Code, Execute and Read    
    */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // 0010 = > Descriptor Type: Data, Read and Write 
    // 0x92 = 0b 1|00|1|0010
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // 0xFA = 0b 1|11|1|1010
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    // 0xF2 = 0b 1|11|1|0010
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
	gdt_flush((uint32_t)&gdt_ptr);
}

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt_entries[num].base_low     = (base & 0xFFFF);
	gdt_entries[num].base_middle  = (base >> 16) & 0xFF;
	gdt_entries[num].base_high    = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low    = (limit & 0xFFFF);
	gdt_entries[num].granularity  = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access       = access;
}

