#ifndef INCLUDE_IDT_H_
#define INCLUDE_IDT_H_

#include "types.h"
#define NUM_IDT_ENTRY 256

#define MASTER_COMMAND_PORT 0x20
#define MASTER_DATA_PORT 0x21
#define SLAVE_COMMAND_PORT 0xA0
#define SLAVE_DATA_PORT 0xA1

#define MASTER_VEC_OFFSET 0x20
#define SLAVE_VEC_OFFSET 0x28

#define ICW1_ICW4 0x01 // ICW4 will be present
#define ICW1_INIT 0x10
#define ICW4_8086 0x01
#define PIC_EOI 0x20

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

void irq_handler(pt_regs *regs);

#define  IRQ0     32
#define  IRQ1     33
#define  IRQ2     34
#define  IRQ3     35
#define  IRQ4     36
#define  IRQ5     37
#define  IRQ6     38
#define  IRQ7     39
#define  IRQ8     40
#define  IRQ9     41
#define  IRQ10    42
#define  IRQ11    43
#define  IRQ12    44
#define  IRQ13    45
#define  IRQ14    46
#define  IRQ15    47

// IRQ: Interrupt Request
void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();

#endif 	// INCLUDE_IDT_H_
