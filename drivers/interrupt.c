#include "interrupt.h"
#include "stm32l4xx.h"

IRQn_Type VectorTable;

int init_interrupt(){
    int res = 0;
    NVIC->ISER[0] |= 0x1U << VectorTable.
}