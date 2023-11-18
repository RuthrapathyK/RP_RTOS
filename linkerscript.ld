#Mention the address of the first function to be executed in elf file which helps the debugger to identify it
ENTRY(main)

MEMORY
{
    FLASH(rx):ORIGIN = 0x00000000, LENGTH = 256K
    SRAM(rwx):ORIGIN = 0x20000000, LENGTH = 32K
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
        *(.data)
    }> SRAM AT>FLASH

    .bss :
    {
        *(.bss)
    }> SRAM
}