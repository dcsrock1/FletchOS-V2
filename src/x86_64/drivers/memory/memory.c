#include <drivers/memory.h>
#include <util/io.h>
#include <util/stdint.h>
#include <util/stddef.h>
#include <util/string.h>

extern char __heap_start;
extern char __heap_end;

uint8_t kernel_memory_pool[KERNEL_MEMORY_POOL_SIZE];
uint8_t user_memory_pool[USER_MEMORY_POOL_SIZE];
Block* kernel_free_list = (Block*)kernel_memory_pool;
Block* user_free_list = (Block*)user_memory_pool;


void init_memory() {
    kernel_free_list->size = KERNEL_MEMORY_POOL_SIZE - BLOCK_SIZE;
    kernel_free_list->next = 0;
    kernel_free_list->free = 1;
    user_free_list->size = USER_MEMORY_POOL_SIZE - BLOCK_SIZE;
    user_free_list->next = 0;
    user_free_list->free = 1;
}


void split_block(Block* block, size_t size) {
    Block* new_block = (Block*)((char*)block + BLOCK_SIZE + size);
    new_block->size = block->size - size - BLOCK_SIZE;
    new_block->next = block->next;
    new_block->free = 1;

    block->size = size;
    block->next = new_block;
    block->free = 0;
}

void merge_free_blocks(Block* current) {
    while (current != 0 && current->next != 0) {
        if (current->free && current->next->free) {
            current->size += BLOCK_SIZE + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

Block* find_free_block(Block* current, size_t size) {
    while (current != 0) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return 0;
}

void free(void* ptr) {
    if (ptr == 0) {
        return;
    }
    Block* block = (Block*)((char*)ptr - BLOCK_SIZE);
    block->free = 1;
    merge_free_blocks(user_free_list);
}

void *malloc(size_t size) {
        if (size <= 0) {
        return 0;
    }

    Block* block = find_free_block(user_free_list, size);
    if (block == 0) {
        return 0;  
    }

    if (block->size > size + BLOCK_SIZE) {
        split_block(block, size);
    } else {
        block->free = 0;
    }

    return (void*)((char*)block + BLOCK_SIZE + USER_MEMORY_POOL_BASE);
}

void *calloc(size_t nmemb, size_t size) {
    size_t total_size = nmemb * size;
    void* ptr = malloc(total_size);
    if (ptr == 0) {
        return 0;
    }
    memset(ptr, 0, total_size);
    
    return ptr;
}

void *realloc(void* ptr, size_t size) {
    if (ptr == 0) {
        return malloc(size);
    }
    if (size == 0) {
        free(ptr);
        return 0;
    }
    Block* block = (Block*)((char*)ptr - BLOCK_SIZE);
    if (block->size >= size) {
        return ptr;
    }
    void* new_ptr = malloc(size);
    if (new_ptr == 0) {
        return 0;
    }
    memcpy(new_ptr, ptr, block->size);
    free(ptr);
    return new_ptr;
}

void kfree(void* ptr) {
    if (ptr == 0) {
        return;
    }
    Block* block = (Block*)((char*)ptr - BLOCK_SIZE);
    block->free = 1;
    merge_free_blocks(kernel_free_list);
}

void *kmalloc(size_t size) {
        if (size <= 0) {
        return 0;
    }

    Block* block = find_free_block(kernel_free_list, size);
    if (block == 0) {
        return 0;  
    }

    if (block->size > size + BLOCK_SIZE) {
        split_block(block, size);
    } else {
        block->free = 0;
    }

    return (void*)((char*)block + BLOCK_SIZE + KERNEL_MEMORY_POOL_BASE);
}

void *kcalloc(size_t nmemb, size_t size) {
    size_t total_size = nmemb * size;
    void* ptr = kmalloc(total_size);
    if (ptr == 0) {
        return 0;
    }
    memset(ptr, 0, total_size);
    
    return ptr ;
}

void *krealloc(void* ptr, size_t size) {
    if (ptr == 0) {
        return kmalloc(size);
    }
    if (size == 0) {
        kfree(ptr);
        return 0;
    }
    Block* block = (Block*)((char*)ptr - BLOCK_SIZE + KERNEL_MEMORY_POOL_BASE);
    if (block->size >= size) {
        return ptr;
    }
    void* new_ptr = kmalloc(size);
    if (new_ptr == 0) {
        return 0;
    }
    memcpy(new_ptr, ptr, block->size);
    kfree(ptr);
    return new_ptr;
}
