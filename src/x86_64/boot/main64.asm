global long_mode_start
global load_pml4
global load_idt
global isrCommon
global keyboard_handler
global pit_handler
extern kernel_main
extern kernel_entry
section .text
bits 64

%macro pushAll 0
      push   rax
      push   rcx
      push   rdx
      push   rbx
      push   rbp
      push   rsi
      push   rdi
      push r8
      push r9
      push r10
      push r11
      push r12
      push r13
      push r14
      push r15
%endmacro

%macro popAll 0
      pop r14
      pop r13
      pop r12
      pop r11
      pop r10
      pop r9
      pop r8
      pop      rdi
      pop      rsi
      pop      rbp
      pop      rbx
      pop      rdx
      pop      rcx
      pop      rax
%endmacro

long_mode_start:
	mov ax, 0   
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
	mov ss, ax
	call kernel_entry
	ret

load_pml4:
  	mov rax, rdi
  	mov cr3, rax
	mov rdx, cr4
  	or  rdx, (1 << 5)
  	mov cr4, rdx
	mov cr0, rbx
	or rbx, (1 << 63)
	mov cr0, rbx
  	; Now reload the segment registers (CS, DS, SS, etc.) with the appropriate segment selectors...
  	; Reload CS with a 64-bit code selector by performing a long jmp
	push 0x08
	lea rax, [rel .fret]
	retfq
	.fret:
		mov   ax, 0x10 ; 0x10 is a stand-in for your data segment
   		mov   ds, ax
   		mov   es, ax
   		mov   fs, ax
   		mov   gs, ax
   		mov   ss, ax
		ret
	call kernel_main
	ret

	
extern IDTp
load_idt:      
    lidt [IDTp]
    sti
    ret

extern keyboard_driver
keyboard_handler:
	cli
	pushAll
	call keyboard_driver
	popAll
	sti
	iretq

extern pit_driver
pit_handler:
	cli
	pushAll
	call pit_driver
	popAll
	sti
	iretq

extern isrHandler

isrCommon:
	pushAll
	extern isrHandler
	call isrHandler
	popAll
	sti
	iretq

global isr2
isr2:
	cli
	pushAll
	extern NMI
	call NMI
	popAll
	sti
	iretq
global isr3
isr3:
	cli
	pushAll
	extern brkINT
	call brkINT
	popAll
	sti
	iretq
global isr8
isr8: 
	cli
	pushAll
	extern double_fault
	call double_fault
	popAll
	sti
	iretq
global isr10
isr10:
	cli
	pushAll
	extern TSSF
	call TSSF
	popAll
	sti
	iretq
global isr11
isr11:
	cli
	pushAll
	extern SNF
	call SNF
	popAll
	sti
	iretq
global isr12
isr12:
	cli
	pushAll
	extern SSF
	call SSF
	popAll
	sti
	iretq
global isr13
isr13:
	cli
	pushAll
	extern GPF
	call GPF
	popAll
	sti
	iretq
global isr14
isr14:
	cli
	pushAll
	extern PF
	call PF
	popAll
	sti
	iretq


%macro ISR_NOERRCODE 1
  global isr%1
  isr%1:
    cli
    jmp isrCommon
%endmacro


ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_NOERRCODE 9
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

section .rodata
gdt64:
    dq 0x0000000000000000  ; Null segment
    dq 0x00A09A0000000000  ; Kernel code segment (DPL=0, 64-bit)
    dq 0x00A0920000000000  ; Kernel data segment (DPL=0)
    dq 0x00A0FA0000000000  ; User code segment (DPL=3, 64-bit)
    dq 0x00A0F20000000000  ; User data segment (DPL=3)
gdtr64:
    dw gdt64_end - gdt64 - 1
    dd gdt64
gdt64_end:
