#include "drivers/util/io.h"

void outb(uint16_t port, uint8_t val) {
    asm volatile("outb %1, %0" : : "dN"(port), "a"(val));
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

uint16_t inw(uint16_t _port) {
    uint16_t rv;
    asm volatile ("inw %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outw(uint16_t _port, uint16_t _data) {
    asm volatile ("outw %1, %0" : : "dN" (_port), "a" (_data));
}

uint32_t indw(uint16_t _port) {
    uint32_t rv;
    asm volatile ("inl %%dx, %%eax" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outdw(uint16_t _port, uint32_t _data) {
    asm volatile ("outl %%eax, %%dx" : : "dN" (_port), "a" (_data));
}