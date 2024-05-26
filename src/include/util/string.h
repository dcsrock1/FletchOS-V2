#pragma once
#include <util/stdint.h>
#include <util/stddef.h>

void reverse(char str[], uint32_t length);
char* itoa(uint32_t num, char* str, int base);

void* memset(void* ptr, int value, size_t num);
void* memmove(void* dest, const void* src, size_t num);
void* memcpy(void* dest, const void* src, size_t num);
