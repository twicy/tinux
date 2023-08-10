[GLOBAL gdt_flush]

gdt_flush:
	mov eax, [esp+4]
    ; gdt_flush is declared as void gdt_flush(uint32_t)
    ; the above saves the input parameter into %eax
	lgdt [eax]
    ; the above load the value in %eax into gdt register

	; set PE bit in r0 register
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	mov ax, 0x10
    ; each gdt_entry_t is 64 bit or 8 bytes in size
    ; 0x10 is the offset to kernel data segment
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush
    ; cannot update cs register directly
    ; flush pipelines and caches
.flush:
	ret
