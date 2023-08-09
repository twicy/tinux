#ifndef INCLUDE_IDT_H_
#define INCLUDE_IDT_H_

#include "types.h"
#define NUM_IDT_ENTRY 256

void init_idt();

typedef
struct idt_entry_t {
	uint16_t offset_low;
	uint16_t segment_selector;
	uint8_t  always0;
	uint8_t  flags;
	uint16_t offset_high;
}__attribute__((packed)) idt_entry_t;

// IDTR
typedef
struct idt_ptr_t {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idt_ptr_t;

// 寄存器类型
typedef
struct pt_regs_t {
	uint32_t ds;
	uint32_t edi;
	uint32_t esi; 
	uint32_t ebp;
	uint32_t esp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;
	uint32_t int_no;
	uint32_t err_code;
	uint32_t eip;
	uint32_t cs; 		
	uint32_t eflags;
	uint32_t useresp;
	uint32_t ss;
} pt_regs;


typedef void (*interrupt_handler_t)(pt_regs *);

void register_interrupt_handler(uint8_t n, interrupt_handler_t h);
void isr_handler(pt_regs *regs);

// ISR: interrupt service routine
void isr0();
void isr1();
void isr2();
void isr3();
void isr4();
void isr5();
void isr6();
void isr7();
void isr8();
void isr9();
void isr10();
void isr11();
void isr12();
void isr13();
void isr14();
void isr15();
void isr16();
void isr17();
void isr18();
void isr19();
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();

void isr255();

#endif 	// INCLUDE_IDT_H_
