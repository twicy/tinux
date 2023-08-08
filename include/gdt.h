/*
 * =====================================================================================
 *
 *       Filename:  gdt.h
 *
 *    Description:  GDT 描述符定义
 *
 *        Version:  1.0
 *        Created:  2013年11月07日 16时16分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef INCLUDE_GDT_H_
#define INCLUDE_GDT_H_

#include "types.h"

// reference: Understanging the Linux Kernel, 3rd edition; P39 Figure 2-3
typedef
struct gdt_entry_t {
	// BASE: linear address of the first byte of the segment
	// LIMIT: offset of the last memory cell in the segment
	uint16_t limit_low; // LIMIT(0-15)
	uint16_t base_low; // BASE(0-15)
	uint8_t  base_middle; // BASE(16-23)
	uint8_t  access;        // 1, DPL, S, TYPE
	// S: if set to 0, it is a system segment; otherwise normal code/data segment
	// TYPE: segment type and access rights
	// DPL: Descriptor Privilege Level
	uint8_t  granularity; 	// G,B,O,AVL, LIMIT(16-19)
	// G: granularity; if set to 0, segment size is in bytes; if set to 1, in 4096 bytes, or 4K
	uint8_t  base_high;     // BASE(24-31)
} __attribute__((packed)) gdt_entry_t;

typedef
struct gdt_ptr_t {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

void init_gdt();

extern void gdt_flush(uint32_t);

#endif
