#pragma once

#include <util/stddef.h>
#include <util/stdint.h>



typedef struct Block {
    uint32_t size;
    struct Block* next;
    uint8_t free;
} Block;

#define BLOCK_SIZE sizeof(Block) 
#define KERNEL_MEMORY_POOL_SIZE 0x80000000
#define KERNEL_MEMORY_POOL_BASE 0xffffffff00010000
#define USER_MEMORY_POOL_SIZE 0x7ffff 
#define USER_MEMORY_POOL_BASE 0x0000000000000000

void init_memory();
void kfree(void* ptr);
void *kmalloc(size_t length);
void *krealloc(void* ptr, size_t length);
void *kcalloc(size_t nmemb, size_t size);
void free(void* ptr);
void *malloc(size_t length);
void *realloc(void* ptr, size_t length);
void *calloc(size_t nmemb, size_t size);


