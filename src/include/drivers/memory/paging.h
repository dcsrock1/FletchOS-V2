#pragma once

#include <util/stdint.h>


#define PAGE_SIZE 4096
#define PAGE_ENTRIES 1024

#define PML4_INDEX(addr) (((addr) >> 39) & 0x1FF)
#define PDPT_INDEX(addr) (((addr) >> 30) & 0x1FF)
#define PD_INDEX(addr) (((addr) >> 21) & 0x1FF)
#define PT_INDEX(addr) (((addr) >> 12) & 0x1FF)

typedef uint64_t page_entry_t;

void init_page_table();
extern void load_pml4(uint64_t pml4_addr);
void setup_paging();