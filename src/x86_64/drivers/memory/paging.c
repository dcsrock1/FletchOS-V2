#include <drivers/memory/paging.h>
#include <util/string.h>

#define PAGE_PRESENT 0x1
#define PAGE_WRITE 0x2
#define PAGE_USER 0x4

page_entry_t pml4[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));
page_entry_t pdpt[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));
page_entry_t pd[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));
page_entry_t pt[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));

void init_page_table() {
    memset(pml4, 0, sizeof(pml4));
    memset(pdpt, 0, sizeof(pdpt));
    memset(pd, 0, sizeof(pd));
    memset(pt, 0, sizeof(pt));

    // Map the PML4 to the PDPT
    pml4[0] = ((uint64_t)pdpt) | 3; // Present, Write, Supervisor

    // Map the PDPT to the PD
    pdpt[0] = ((uint64_t)pd) | 3; // Present, Write, Supervisor

    // Map the PD to the PT
    pd[0] = ((uint64_t)pt) | 3; // Present, Write, Supervisor

    for (int i = 0; i < 256; i++) {
        pt[i] = ((0xC0000000 + i * PAGE_SIZE) & 0x000FFFFFFFFFF000) | PAGE_PRESENT | PAGE_WRITE; // Present, Write, Supervisor
    }


    for (int i = 0; i < 524287; i++) {
        pt[i] = ((0x0000000000000000 + i * PAGE_SIZE) & 0x000FFFFFFFFFF000) | PAGE_PRESENT | PAGE_WRITE | PAGE_USER; // Present, Write, User
    }
}

void map_user_space(uint64_t vaddr, uint64_t paddr, size_t size) {
    size_t num_pages = size / PAGE_SIZE;
    for (size_t i = 0; i < num_pages; i++) {
        uint64_t v = vaddr + (i * PAGE_SIZE);
        uint64_t p = paddr + (i * PAGE_SIZE);

        size_t pml4_index = PML4_INDEX(v);
        size_t pdpt_index = PDPT_INDEX(v);
        size_t pd_index = PD_INDEX(v);
        size_t pt_index = PT_INDEX(v);

        if (!(pml4[pml4_index] & 1)) {
            pml4[pml4_index] = (uint64_t)pdpt | 7; // Present, Write, User
            memset(pdpt, 0, PAGE_SIZE);
        }

        if (!(pdpt[pdpt_index] & 1)) {
            pdpt[pdpt_index] = (uint64_t)pd | 7; // Present, Write, User
            memset(pd, 0, PAGE_SIZE);
        }

        if (!(pd[pd_index] & 1)) {
            pd[pd_index] = (uint64_t)pt | 7; // Present, Write, User
            memset(pt, 0, PAGE_SIZE);
        }

        pt[pt_index] = p | 7; // Present, Write, User
    }
}

// Function to load the PML4 table

void setup_paging() {
    init_page_table();
    load_pml4((uint64_t)pml4);
}