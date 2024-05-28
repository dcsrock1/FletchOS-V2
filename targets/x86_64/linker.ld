ENTRY(start)

SECTIONS
{
    . = 0xffffffff00000000;
    .boot :
    {
        *(.multiboot_header)
    }
    .text ALIGN(16):
    {
        *(.text)
    }
    .data ALIGN(8):
    {
        *(.data)
    }
    .bss ALIGN(8):
    {
        *(.bss)
    }
}

