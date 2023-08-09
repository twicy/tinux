#include "common.h"
#include "string.h"
#include "elf.h"

/**
 * ELF executable consist of an ELF header, followed by program header table
 * of a section header table or both.
 * 
 * ELF header is always at offset 0 of the file.
 * 
 * program header table and section header table are defined in ELF header.
 */

elf_t elf_from_multiboot(multiboot_t *mb)
{
	int i;
	elf_t elf;
	// mb.addr points to an elf_section_header_t array
	elf_section_header_t *sh = (elf_section_header_t *)mb->addr;

	// elf_section_header_t.addr
	// mb->shndx is the string table index
	uint32_t shstrtab = sh[mb->shndx].addr;
	// for each entry
	for (i = 0; i < mb->num; i++) {
		const char *name = (const char *)(shstrtab + sh[i].name);
		// extract information from multiboot provided by GRUB
		// this sections holds strings that represent the names associated with symbol table entries
		if (strcmp(name, ".strtab") == 0) {
			elf.strtab = (const char *)sh[i].addr;
			elf.strtabsz = sh[i].size;
		}
		// this section holds a symbol table
		if (strcmp(name, ".symtab") == 0) {
			elf.symtab = (elf_symbol_t *)sh[i].addr;
			elf.symtabsz = sh[i].size;
		}
	}

	return elf;
}

const char *elf_lookup_symbol(uint32_t addr, elf_t *elf)
{
	int i;

	for (i = 0; i < (elf->symtabsz / sizeof(elf_symbol_t)); i++) {
		if (ELF32_ST_TYPE(elf->symtab[i].info) != 0x2) {
		      continue;
		}
		if ((addr >= elf->symtab[i].value) &&
			(addr < (elf->symtab[i].value + elf->symtab[i].size))) {
			return (const char *)((uint32_t)elf->strtab + elf->symtab[i].name);
		}
	}

	return NULL;
}

