ENTRY(start)

SECTIONS
{
    . = 1M;
    .boot :
    {
        KEEP(*(.multiboot_header))
    }
    .text :
    {
        *(.text)
    }
    .bss ALIGN (0x8000) : 
    {
        *(COMMON)
        *(.bss)
    }
}