#include <drivers/idt.h>
#include <util/string.h>
#include <drivers/video.h>
#include <drivers/memory.h>

idtEntry IDT[256] __attribute__((section(".data")));
idtPointer IDTp;
extern void load_idt();
extern void pit_handler();
extern void keyboard_handler();


void setIDT(uint8_t number, uint64_t base, uint16_t selector, uint8_t flags) {
   IDT[number].offset_1 = base & 0xFFFF;
   IDT[number].offset_2 = (base >> 16) & 0xFFFF;
   IDT[number].offset_3 = (base >> 32) & 0xFFFFFFFF;
   IDT[number].selector = selector;
   IDT[number].type_attributes = flags;
   IDT[number].ist = 0;
   IDT[number].zero = 0;
}

void init_IDT() {
    setIDT(0, (uint64_t)isr0, 0x08, 0x8F);
    setIDT(1, (uint64_t)isr1, 0x08, 0x8F);
    setIDT(2, (uint64_t)isr2, 0x08, 0x8F);
    setIDT(3, (uint64_t)isr3, 0x08, 0x8F);
    setIDT(4, (uint64_t)isr4, 0x08, 0x8F);
    setIDT(5, (uint64_t)isr5, 0x08, 0x8F);
    setIDT(6, (uint64_t)isr6, 0x08, 0x8F);
    setIDT(7, (uint64_t)isr7, 0x08, 0x8F);
    setIDT(8, (uint64_t)isr8, 0x08, 0x8F);
    setIDT(9, (uint64_t)isr9, 0x08, 0x8F);
    setIDT(10, (uint64_t)isr10, 0x08, 0x8F);
    setIDT(11, (uint64_t)isr11, 0x08, 0x8F);
    setIDT(12, (uint64_t)isr12, 0x08, 0x8F);
    setIDT(13, (uint64_t)isr13, 0x08, 0x8F);
    setIDT(14, (uint64_t)isr14, 0x08, 0x8F);
    setIDT(15, (uint64_t)isr15, 0x08, 0x8F);
    setIDT(16, (uint64_t)isr16, 0x08, 0x8F);
    setIDT(17, (uint64_t)isr17, 0x08, 0x8F);
    setIDT(18, (uint64_t)isr18, 0x08, 0x8F);
    setIDT(19, (uint64_t)isr19, 0x08, 0x8F);
    setIDT(20, (uint64_t)isr20, 0x08, 0x8F);
    setIDT(21, (uint64_t)isr21, 0x08, 0x8F);
    setIDT(22, (uint64_t)isr22, 0x08, 0x8F);
    setIDT(23, (uint64_t)isr23, 0x08, 0x8F);
    setIDT(24, (uint64_t)isr24, 0x08, 0x8F);
    setIDT(25, (uint64_t)isr25, 0x08, 0x8F);
    setIDT(26, (uint64_t)isr26, 0x08, 0x8F);
    setIDT(27, (uint64_t)isr27, 0x08, 0x8F);
    setIDT(28, (uint64_t)isr28, 0x08, 0x8F);
    setIDT(29, (uint64_t)isr29, 0x08, 0x8F);
    setIDT(30, (uint64_t)isr30, 0x08, 0x8F);
    setIDT(31, (uint64_t)isr31, 0x08, 0x8F);
    setIDT(32, (uint64_t)pit_handler, 0x08, 0x8E);
    setIDT(33, (uint64_t)keyboard_handler, 0x08, 0x8E);
    IDTp.limit = (sizeof(idtEntry) * 256) - 1;
    IDTp.base = (uint64_t) &IDT;
    load_idt();
}

void isrHandler(uint64_t rbp, uint64_t rsi, uint64_t rdi, uint64_t rax, uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    char* str = 0;
    print("rbp: ");
    println(itoa(rbp, str, 10));
    str = 0;
    print("rsi: ");
    println(itoa(rsi, str, 10));
    str = 0;
    print("rdi: ");
    println(itoa(rdi, str, 10));
    str = 0;
    print("rax: ");
    println(itoa(rax, str, 10));
    str = 0;
    print("rbx: ");
    println(itoa(rbx, str, 10));
    str = 0;
    print("rcx: ");
    println(itoa(rdx, str, 10));
    str = 0;
}