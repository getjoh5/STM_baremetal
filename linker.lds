ENTRY(_start)

MEMORY
{
    flash (rx)  : ORIGIN = 0x08000000, LENGTH = 1M
    sram1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
    sram2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
}

_stack = ORIGIN(sram2) + LENGTH(sram2);

SECTIONS
{
    /* Le Cortex-M lit cette table directement apres reset. */
    .isr_vector : {
        KEEP(*(.isr_vector))
    } > flash

    /* Code minimal execute depuis la flash avant la copie en RAM. */
    .text_crt0 : {
        KEEP(*(.text_crt0))
        KEEP(*(.text_crt0*))
    } > flash

    /* Code applicatif execute en SRAM1, mais stocke en flash dans l'image ELF. */
    .text : {
        . = ALIGN(4);
        _stext = .;
        *(.text)
        *(.text*)
        . = ALIGN(4);
        _etext = .;
    } > sram1 AT> flash
    _ld_stext = LOADADDR(.text);

    /* Les constantes restent en flash: pas besoin de les copier au demarrage. */
    .rodata : {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } > flash

    /* Variables initialisees: adresse d'execution en SRAM1, image en flash. */
    .data : {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > sram1 AT> flash
    _ld_sdata = LOADADDR(.data);

    /* Variables non initialisees: seulement en SRAM1, remises a zero au reset. */
    .bss : {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > sram1
}
