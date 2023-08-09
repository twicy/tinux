#include "types.h"
#include "string.h"
#include "idt.h"
#include "console.h"
#include "printk.h"

idt_entry_t idt_entries[NUM_IDT_ENTRY];
idt_ptr_t idt_ptr;
interrupt_handler_t interrupt_handlers[NUM_IDT_ENTRY];

extern void idt_flush(uint32_t);

void isr_handler(pt_regs *regs)
{
	if (interrupt_handlers[regs->int_no]) {
	      interrupt_handlers[regs->int_no](regs);
	} else {
		printk("Unhandled interrupt with code: %d\n", regs->int_no);
	}
}

void register_interrupt_handler(uint8_t n, interrupt_handler_t h)
{
	interrupt_handlers[n] = h;
}

static void idt_set_gate(uint8_t num, uint32_t offset, uint16_t segment_selector, uint8_t flags)
{
	idt_entries[num].offset_low = offset & 0xFFFF;
	idt_entries[num].offset_high = (offset >> 16) & 0xFFFF;

	idt_entries[num].segment_selector = segment_selector;
	idt_entries[num].always0 = 0;

	idt_entries[num].flags = flags;  // | 0x60
}

void init_idt()
{	
	memset((uint8_t *)&interrupt_handlers, 0, sizeof(interrupt_handler_t) * NUM_IDT_ENTRY);
	
	idt_ptr.limit = sizeof(idt_entry_t) * NUM_IDT_ENTRY - 1;
	idt_ptr.base  = (uint32_t)&idt_entries;
	
	memset((uint8_t *)&idt_entries, 0, sizeof(idt_entry_t) * NUM_IDT_ENTRY);

    // segment selector: 0x8
    // 0x8E = 0b 1|00|01110
    // P = 1, present in memory
    // DPL = 0, kernel mode
    // D = 1, sizeof gate = 32 bits

	idt_set_gate( 0, (uint32_t)isr0,  0x08, 0x8E);
	idt_set_gate( 1, (uint32_t)isr1,  0x08, 0x8E);
	idt_set_gate( 2, (uint32_t)isr2,  0x08, 0x8E);
	idt_set_gate( 3, (uint32_t)isr3,  0x08, 0x8E);
	idt_set_gate( 4, (uint32_t)isr4,  0x08, 0x8E);
	idt_set_gate( 5, (uint32_t)isr5,  0x08, 0x8E);
	idt_set_gate( 6, (uint32_t)isr6,  0x08, 0x8E);
	idt_set_gate( 7, (uint32_t)isr7,  0x08, 0x8E);
	idt_set_gate( 8, (uint32_t)isr8,  0x08, 0x8E);
	idt_set_gate( 9, (uint32_t)isr9,  0x08, 0x8E);
	idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
	idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
	idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
	idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
	idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
	idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
	idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
	idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
	idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
	idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
	idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
	idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
	idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
	idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
	idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
	idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
	idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
	idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
	idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
	idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
	idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
	idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

	idt_set_gate(255, (uint32_t)isr255, 0x08, 0x8E);

	idt_flush((uint32_t)&idt_ptr);
}
