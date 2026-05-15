#ifndef INTERRUPT_T
#define INTERRUPT_T

#define NVIC_ISER_BASE  0x00000000U

extern IRQn_Type VectorTable;

int init_interrupt();


#endif