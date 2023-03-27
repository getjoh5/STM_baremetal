#include <stdint.h>
#include <string.h>
#include "stm32l475xx.h"
#include"startup_filel.h"

#define SRAM1_start 0x20000000U
#define SRAM1_size (97U+1024U)
#define SRAM1_end ((SRAM1_start )+ (SRAM1_size))
#define SRAM2_start 0x10000000U
#define SRAM2_size (28U+1024U)
#define SRAM2_end ((SRAM2_start )+ (SRAM2_size))
//#define START_STACK SRAM2_end 


//NVIC
volatile uint32_t *const NVIC_ICER = (uint32_t *)0XE000E180;
//volatile uint32_t *const _VTOR = (uint32_t *)0xE000ED08;





#define MA_FONCTION(irq_truc) void __attribute__((weak)) irq_truc(void){__disable_irq();default_handler();}
MA_FONCTION(NonMaskableInt_Handler);
MA_FONCTION( HardFault_Handler);
MA_FONCTION( MemoryManagement_Handler);
MA_FONCTION( BusFault_Handler);
MA_FONCTION( UsageFault_Handler);
MA_FONCTION( SVCall_Handler);

MA_FONCTION( PendSV_Handler);
MA_FONCTION( SysTick_Handler);
MA_FONCTION( WWDG_Handler);
MA_FONCTION( PVD_PVM_Handler);
MA_FONCTION( TAMP_STAMP_Handler);
MA_FONCTION( RTC_WKUP_Handler);
MA_FONCTION( FLASH_Handler);
MA_FONCTION( RCC_Handler);
MA_FONCTION( EXTI0_Handler);
MA_FONCTION( EXTI1_Handler);
MA_FONCTION( EXTI2_Handler);
MA_FONCTION( EXTI3_Handler);
MA_FONCTION( EXTI4_Handler);
MA_FONCTION( DMA1_Channel1_Handler);
MA_FONCTION( DMA1_Channel2_Handler);
MA_FONCTION( DMA1_Channel3_Handler);
MA_FONCTION( DMA1_Channel4_Handler);
MA_FONCTION( DMA1_Channel5_Handler);
MA_FONCTION( DMA1_Channel6_Handler);
MA_FONCTION( DMA1_Channel7_Handler);
MA_FONCTION( ADC1_2_Handler);
MA_FONCTION( CAN1_TX_Handler);
MA_FONCTION( CAN1_RX0_Handler);
MA_FONCTION( CAN1_RX1_Handler);
MA_FONCTION( CAN1_SCE_Handler);
MA_FONCTION( EXTI9_5_Handler);
MA_FONCTION( IM1_BRK_TIM15_Handler);
MA_FONCTION( TIM1_UP_TIM16_Handler);
MA_FONCTION( TRG_COM_TIM17_Handler);
MA_FONCTION( TIM1_CC_Handler);
MA_FONCTION( TIM2_Handler);
MA_FONCTION( TIM3_Handler);
MA_FONCTION( TIM4_Handler);
MA_FONCTION( I2C1_EV_Handler);    
MA_FONCTION( I2C1_ER_Handler);  
MA_FONCTION( I2C2_EV_Handler);   
MA_FONCTION( I2C2_ER_Handler);
MA_FONCTION( SPI1_Handler);
MA_FONCTION( SPI2_Handler);
MA_FONCTION( USART1_Handler);  
MA_FONCTION( USART2_Handler);  
MA_FONCTION( USART3_Handler);  
MA_FONCTION( EXTI15_10_Handler);
MA_FONCTION( RTC_Alarm_Handler);
MA_FONCTION( DFSDM1_FLT3_Handler);
MA_FONCTION( TIM8_BRK_Handler);
MA_FONCTION( TIM8_UP_Handler);
MA_FONCTION( TIM8_TRG_COM_Handler);
MA_FONCTION( TIM8_CC_Handler);
MA_FONCTION( ADC3_Handler);
MA_FONCTION( FMC_Handler);
MA_FONCTION( SDMMC1_Handler);
MA_FONCTION( TIM5_Handler);
MA_FONCTION( SPI3_Handler);
MA_FONCTION( UART4_Handler);
MA_FONCTION( UART5_Handler);
MA_FONCTION( TIM6_DAC_Handler);
MA_FONCTION( TIM7_Handler);
MA_FONCTION( DMA2_Channel1_Handler);
MA_FONCTION( DMA2_Channel2_Handler);
MA_FONCTION( DMA2_Channel3_Handler);
MA_FONCTION( DMA2_Channel4_Handler);
MA_FONCTION( DMA2_Channel5_Handler);
MA_FONCTION( DFSDM1_FLT0_Handler);
MA_FONCTION( DFSDM1_FLT1_Handler);
MA_FONCTION( DFSDM1_FLT2_Handler);
MA_FONCTION( COMP_Handler);
MA_FONCTION( LPTIM1_Handler);   
MA_FONCTION( LPTIM2_Handler);
MA_FONCTION( OTG_FS_Handler);
MA_FONCTION( DMA2_Channel6_Handler);
MA_FONCTION( DMA2_Channel7_Handler);
MA_FONCTION( LPUART1_Handler);
MA_FONCTION( QUADSPI_Handler);
MA_FONCTION( I2C3_EV_Handler);
MA_FONCTION( I2C3_ER_Handler);
MA_FONCTION( SAI1_Handler);
MA_FONCTION( SAI2_Handler);
MA_FONCTION( SWPMI1_Handler);
MA_FONCTION( TSC_Handler);
MA_FONCTION( RNG_Handler);
MA_FONCTION( FPU_Handler);


// //void NonMaskableInt_Handler __attribute__((weak, alias("default_handler")));
// //void HardFault_Handler __attribute__((weak, alias("default_handler")));
extern uint32_t _stack;
extern void _start();

void * __attribute__ ((section(".isr_vector")))  vectors[] ={
    &_stack,
     _start,
     NonMaskableInt_Handler,
     HardFault_Handler,
     MemoryManagement_Handler,
     BusFault_Handler,
     UsageFault_Handler,
     0,
     0,
     0,
     0,
     SVCall_Handler,
     0,
     0,
     PendSV_Handler,
     SysTick_Handler,
     WWDG_Handler,
     PVD_PVM_Handler,
     TAMP_STAMP_Handler,
     RTC_WKUP_Handler,
     FLASH_Handler,
     RCC_Handler,
     EXTI0_Handler,
     EXTI1_Handler,
     EXTI2_Handler,
     EXTI3_Handler,
     EXTI4_Handler,
     DMA1_Channel1_Handler,
     DMA1_Channel2_Handler,
     DMA1_Channel3_Handler,
     DMA1_Channel4_Handler,
     DMA1_Channel5_Handler,
     DMA1_Channel6_Handler,
     DMA1_Channel7_Handler,
     ADC1_2_Handler,
     CAN1_TX_Handler,
     CAN1_RX0_Handler,
     CAN1_RX1_Handler,
     CAN1_SCE_Handler,
     EXTI9_5_Handler,
     IM1_BRK_TIM15_Handler,
     TIM1_UP_TIM16_Handler,
     TRG_COM_TIM17_Handler,
     TIM1_CC_Handler,
     TIM2_Handler,
     TIM3_Handler,
     TIM4_Handler,
     I2C1_EV_Handler,
     I2C1_ER_Handler,
     I2C2_EV_Handler,
     I2C2_ER_Handler,
     SPI1_Handler,
     SPI2_Handler,
     USART1_Handler,
     USART2_Handler,
     USART3_Handler,
     EXTI15_10_Handler,
     RTC_Alarm_Handler,
     DFSDM1_FLT3_Handler,
     TIM8_BRK_Handler,
     TIM8_UP_Handler,
     TIM8_TRG_COM_Handler,
     TIM8_CC_Handler,
     ADC3_Handler,
     FMC_Handler,
     SDMMC1_Handler,
     TIM5_Handler,
     SPI3_Handler,
     UART4_Handler,
     UART5_Handler,
     TIM6_DAC_Handler,
     TIM7_Handler,
     DMA2_Channel1_Handler,
     DMA2_Channel2_Handler,
     DMA2_Channel3_Handler,
     DMA2_Channel4_Handler,
     DMA2_Channel5_Handler,
     DFSDM1_FLT0_Handler,
     DFSDM1_FLT1_Handler,
     DFSDM1_FLT2_Handler,
     COMP_Handler,
     LPTIM1_Handler,
     LPTIM2_Handler,
     OTG_FS_Handler,
     DMA2_Channel6_Handler,
     DMA2_Channel7_Handler,
     LPUART1_Handler,
     QUADSPI_Handler,
     I2C3_EV_Handler,
     I2C3_ER_Handler,
     SAI1_Handler,
     SAI2_Handler,
     SWPMI1_Handler,
     TSC_Handler,
     RNG_Handler,
     FPU_Handler
};
extern uint32_t _etext,_stext,_edata, _sdata, _ebss, _sbss,_ld_sdata,_ld_stext ;

void Reset_handler()
{
    
    //JE COPIE LES ELEMENT DU .DATA vers la sram1
    uint32_t Size_data=(uint32_t)&_edata-(uint32_t)&_sdata;
    uint32_t Size_text=(uint32_t)&_etext-(uint32_t)&_stext;
    //uint32_t Size_bss=(uint32_t)&_ebss-(uint32_t)&_sbss;
    uint32_t i=0;
    //copie txt de la flash à la ram
    i=0;
    while(i<Size_text){
        const uint8_t * memoire_source_text=(uint8_t *)&_ld_stext;
        uint8_t * memoire_des_text=(uint8_t*)&_stext;
    
        memoire_des_text[i]=memoire_source_text[i];
        i++;
    }
    i=0;
    //copie des variables initialisés du .data
    while(i<Size_data){
        const uint8_t * memoire_source=(uint8_t *)&_ld_sdata;;
        uint8_t * memoire_des =(uint8_t*)&_sdata ;
        memoire_des[i]=memoire_source[i];
        i++;
    }
    //.bss à 0

    for(uint8_t *dst=(uint8_t *)&_sbss;dst<(uint8_t *)&_ebss;dst++){
        *dst=0;
    }

    
    
   
}
// void  irq_init(){
//     SCB->VTOR=vectors;
// }

void default_handler(){
     
    for(;;);
}
