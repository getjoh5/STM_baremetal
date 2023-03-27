#include <stdint.h>
#include "pripherique_config.h"


/*configuration du RCC*/

 

volatile uint32_t *const RCC_EN = (uint32_t *)0x4002104c;
volatile uint32_t *const RCC_RST = (uint32_t *)0x4002102c;
volatile uint32_t *const RCC_CR = (uint32_t *)0x40021000;

/*GPIO_14 LED*/
volatile uint32_t *const GPIO_PUPD_BY = (uint32_t *)0x4800080c;
volatile uint32_t *const GPIO_MODER_GREEN = (uint32_t *)0x48000400;
volatile uint32_t *const GPIO_MODER_BY = (uint32_t *)0x48000800;

volatile uint32_t *const GPIO_BSRR = (uint32_t *)0x48000418;
volatile uint32_t *const GPIO_BSRR_BY = (uint32_t *)0x48000818;
// volatile uint32_t *const gpiob14_res=(uint32_t *)0x48000428;
volatile uint32_t *const GPIO_OTYPE_BY = (uint32_t *)0x48000804;
volatile uint32_t *const GPIO_ODR = (uint32_t *)0x48000414;
volatile uint32_t *const GPIO_ODR_BY = (uint32_t *)0x48000814;
// unsigned int j=0;

void initialisation()
{
    //*RCC_RST=1<<1;
    // uint32_t k=*RCC_CR;
    //*RCC_CR^=(uint32_t)0x1;
    //*RCC_CR |=(1<<16);
    // while(((*RCC_CR)^k)==0);
    *RCC_EN = 0x3 << 1;
    //*GPIO_OTYPE_BY |= 1 << 9;
    *GPIO_MODER_GREEN = (~(*GPIO_MODER_GREEN)) | (1 << 28);
    *GPIO_MODER_BY = (~(*GPIO_MODER_BY)) | (1 << 18);
}

void led(state t)
{
    switch (t)
    {
    case LED_OFF:
      
        *GPIO_OTYPE_BY |= 1 << 9;
        *GPIO_ODR_BY |=(1<<9);
        break;
    case LED_BLUE:
      
        *GPIO_OTYPE_BY &= ~(1 << 9);
        *GPIO_BSRR_BY |= (1 << 25);
        break;
    case LED_YELLOW:
       
       *GPIO_OTYPE_BY &= ~(1 << 9);
        *GPIO_BSRR_BY |= (1 << 9);
        
        break;
    }
}

void allume()
{
    *GPIO_BSRR = (1 << 14);
}
void eteint()
{
    *GPIO_BSRR = (1 << 30);
}


