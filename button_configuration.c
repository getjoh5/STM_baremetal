#include <stdint.h>
#include "button_configuration.h"
#include "pripherique_config.h"
#include "stm32l475xx.h"

//PC 13
//configuration de lorloge et du mode 
// base RCC 0x4002 1000

//base GPIOC 0x4800 0800

volatile uint32_t *const RCC_BUT_EN = (uint32_t *) 0x4002104c;
volatile uint32_t *const RCC_APB2_EN = (uint32_t *) 0x40021060;
volatile uint32_t *const MODER_BUT = (uint32_t *) 0x48000800;

volatile uint32_t *const GPIOC_IDR =  (uint32_t *) 0x48000810; // idr pour lire la valeur du registre
volatile uint32_t *const PUPD_BUT = (uint32_t *) 0x4800080c;

//configuration de ExTI
//base SYSCFG 0x4001 0000
//base de EXTI 0x4001 0400
volatile uint32_t *const SYSCFG_ = (uint32_t *) 0x40010014;
volatile uint32_t *const EXTI_IMR = (uint32_t *) 0x40010400;
volatile uint32_t *const EXTI_RTS =  (uint32_t *) 0x40010408;
volatile uint32_t *const EXTI_FTSR1 =  (uint32_t *) 0x4001040c;
volatile uint32_t *const EXTI_PEN =  (uint32_t *) 0x40010414;
volatile uint32_t *const EXTI_NVIC =  (uint32_t *) 0xE000E100;


//SYSCFG->EXTICR[3]

void int_button()
{
    *RCC_BUT_EN |= (1<<2);
    *RCC_APB2_EN |=(0x1);
    *MODER_BUT &=~(0x3<<26);
    *SYSCFG_  &=~(0xF<<4);
    *SYSCFG_  =0x00000020UL; //activation de la ligne 14c
    //*PUPD_BUT   &=~(0x3<<26);
    //*PUPD_BUT   |=(0x2<<26); // configure en pD
    *EXTI_IMR |=(0x1<<13); 
    *EXTI_RTS &=~(0x1<<13); //rising triger enable
    *EXTI_FTSR1 |=(0x1<<13);
    __enable_irq();
    NVIC_SetPriority(35, 0);
    NVIC_EnableIRQ(40);
}

/* void EXTI15_10_IRQn(){

}  */
 void EXTI15_10_Handler(){
  
    (*GPIO_ODR & ((uint32_t)(0x1)<<14))? eteint():allume();
    *EXTI_PEN |=(0x1<<13);
}
 




