#pragma once

#include <util/stdint.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t _port);
void outw(uint16_t _port, uint16_t _data);
uint32_t indw(uint16_t _port);
void outdw(uint16_t _port, uint32_t _data);
void io_wait();