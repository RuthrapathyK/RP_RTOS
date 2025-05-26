
MEMORY
{
    FLASH(rx):ORIGIN = 0x00000000, LENGTH = 256K
    SRAM(!rx):ORIGIN = 0x20000000, LENGTH = 32K
}

SECTIONS
{
    .text :
    {
        __s_text = .;
        *(.stack_pointer)
        *(.vector_table)
        *(.text)
        *(.rodata)
        __e_text = .;  
    }> FLASH

    .stack :
    {
        . = 0x400;
    }>SRAM

    .data :
    {
        __s_data = .;
        *(.data)
        __e_data = .;
    }> SRAM AT>FLASH

    .bss :
    {
        __s_bss = .;
        *(.bss)
        __e_bss = .;
    }> SRAM
}