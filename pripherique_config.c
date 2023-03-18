#include <stdint.h>
#include "pripherique_config.h"
//#include "stm32l475xx.h"



/*configuration du RCC*/

volatile uint32_t *const RCC_EN=(uint32_t *)0x4002104c;
volatile uint32_t *const RCC_RST= (uint32_t *)0x4002102c;
volatile uint32_t *const RCC_CR= (uint32_t *)0x40021000;







/*GPIO_14 LED*/
volatile uint32_t *const GPIO_PUPD=(uint32_t *)0x4800040c;
volatile uint32_t *const GPIO_MODER=(uint32_t *)0x48000400;
volatile uint32_t *const GPIO_BSRR=(uint32_t *)0x48000418;
//volatile uint32_t *const gpiob14_res=(uint32_t *)0x48000428;
//volatile uint32_t *const GPIO_OTYPE =(uint32_t *)0x48000404;
volatile uint32_t *const GPIO_ODR=(uint32_t *)0x48000414;
//unsigned int j=0;

void initialisation(){
    //*RCC_RST=1<<1;
    //uint32_t k=*RCC_CR;
    //*RCC_CR^=(uint32_t)0x1;
    //*RCC_CR |=(1<<16);
    //while(((*RCC_CR)^k)==0);
    *RCC_EN= 1<<1;
    *GPIO_MODER = (~(*GPIO_MODER))|(1<<28);
    

}
void allume(){
*GPIO_BSRR =(1<<14);

}
void eteint(){
*GPIO_BSRR =(1<<30);

}


