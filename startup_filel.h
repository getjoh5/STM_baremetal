#ifndef S
#define S

#include <stdint.h>

#define BOOT_CODE __attribute__((section(".text_crt0")))

extern uint32_t _stack;
extern void _start(void);

extern uint32_t _stext, _etext, _ld_stext;
extern uint32_t _sdata, _edata, _ld_sdata;
extern uint32_t _sbss, _ebss;

BOOT_CODE void Reset_handler(void);
BOOT_CODE void default_handler(void);


#endif
