ENTRY(Reset_handler)

_star_stack = LENGTH(sram2)+ORIGIN(sram2);

/*region relocation */

MEMORY
{
    flash (rx)  : ORIGIN = 0x08000000, LENGTH = 1M
    sram1 (wx)  : ORIGIN = 0x20000000, LENGTH = 96K
    sram2 (wx)  : ORIGIN = 0x10000000, LENGTH = 32K
    
}



_sdata = ADDR(.data);
_ld_sdata = LOADADDR(.data);
_edata = SIZEOF(.data) + _sdata ;

_stext = ADDR(.text);
_ld_stext = LOADADDR(.text);
_etext = SIZEOF(.text) + ADDR(.text);


SECTIONS{
    .text : {
        *(.text)
    } > sram1 AT >flash
    .rodat : {
        *(.rodata)
    } > flash
    .data : {
        
        *(.data)
        
    } > sram1 AT >flash
    .bss : {
        _sbss = . ; 
        *(.bss)
        *(COMMON)
        _ebss = . ;
    } > sram1
   
}