
MEMORY
{
    FLASH(rx):ORIGIN = 0x00000000, LENGTH = 256K
    SRAM(!rx):ORIGIN = 0x20000000, LENGTH = 32K
}

SECTIONS
{
    .text :
    {
        *(.isr_vector)
        *(.text)
        *(.rodata)  
    }> FLASH

    .data :
    {
        __start_data = .;
        *(.data)
        __end_data = .;
    }> SRAM AT>FLASH

    .bss :
    {
        *(.bss)
    }> SRAM
}