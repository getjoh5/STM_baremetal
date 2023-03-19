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

// void default_handler();
// #define MA_FONCTION(irq_truc) void __attribute__((weak, alias("default_handler"))) irq_truc() 
// void Reset_handler();
// MA_FONCTION(NonMaskableInt_Handler);
// MA_FONCTION( HardFault_Handler);
// MA_FONCTION( MemoryManagement_Handler);
// MA_FONCTION( BusFault_Handler);
// MA_FONCTION( UsageFault_Handler);
// MA_FONCTION( SVCall_Handler);
// MA_FONCTION( DebugMonitor_Handler);
// MA_FONCTION( PendSV_Handler);
// MA_FONCTION( SysTick_Handler);
// MA_FONCTION( WWDG_Handler);
// MA_FONCTION( PVD_PVM_Handler);
// MA_FONCTION( TAMP_STAMP_Handler);
// MA_FONCTION( RTC_WKUP_Handler);
// MA_FONCTION( FLASH_Handler);
// MA_FONCTION( RCC_Handler);
// MA_FONCTION( EXTI0_Handler);
// MA_FONCTION( EXTI1_Handler);
// MA_FONCTION( EXTI2_Handler);
// MA_FONCTION( EXTI3_Handler);
// MA_FONCTION( EXTI4_Handler);
// MA_FONCTION( DMA1_Channel1_Handler);
// MA_FONCTION( DMA1_Channel2_Handler);
// MA_FONCTION( DMA1_Channel3_Handler);
// MA_FONCTION( DMA1_Channel4_Handler);
// MA_FONCTION( DMA1_Channel5_Handler);
// MA_FONCTION( DMA1_Channel6_Handler);
// MA_FONCTION( DMA1_Channel7_Handler);
// MA_FONCTION( ADC1_2_Handler);
// MA_FONCTION( CAN1_TX_Handler);
// MA_FONCTION( CAN1_RX0_Handler);
// MA_FONCTION( CAN1_RX1_Handler);
// MA_FONCTION( CAN1_SCE_Handler);
// MA_FONCTION( EXTI9_5_Handler);
// MA_FONCTION( IM1_BRK_TIM15_Handler);
// MA_FONCTION( TIM1_UP_TIM16_Handler);
// MA_FONCTION( TRG_COM_TIM17_Handler);
// MA_FONCTION( TIM1_CC_Handler);
// MA_FONCTION( TIM2_Handler);
// MA_FONCTION( TIM3_Handler);
// MA_FONCTION( TIM4_Handler);
// MA_FONCTION( I2C1_EV_Handler);    
// MA_FONCTION( I2C1_ER_Handler);  
// MA_FONCTION( I2C2_EV_Handler);   
// MA_FONCTION( I2C2_ER_Handler);
// MA_FONCTION( SPI1_Handler);
// MA_FONCTION( SPI2_Handler);
// MA_FONCTION( USART1_Handler);  
// MA_FONCTION( USART2_Handler);  
// MA_FONCTION( USART3_Handler);  
// MA_FONCTION( EXTI15_10_Handler);
// MA_FONCTION( RTC_Alarm_Handler);
// MA_FONCTION( DFSDM1_FLT3_Handler);
// MA_FONCTION( TIM8_BRK_Handler);
// MA_FONCTION( TIM8_UP_Handler);
// MA_FONCTION( TIM8_TRG_COM_Handler);
// MA_FONCTION( TIM8_CC_Handler);
// MA_FONCTION( ADC3_Handler);
// MA_FONCTION( FMC_Handler);
// MA_FONCTION( SDMMC1_Handler);
// MA_FONCTION( TIM5_Handler);
// MA_FONCTION( SPI3_Handler);
// MA_FONCTION( UART4_Handler);
// MA_FONCTION( UART5_Handler);
// MA_FONCTION( TIM6_DAC_Handler);
// MA_FONCTION( TIM7_Handler);
// MA_FONCTION( DMA2_Channel1_Handler);
// MA_FONCTION( DMA2_Channel2_Handler);
// MA_FONCTION( DMA2_Channel3_Handler);
// MA_FONCTION( DMA2_Channel4_Handler);
// MA_FONCTION( DMA2_Channel5_Handler);
// MA_FONCTION( DFSDM1_FLT0_Handler);
// MA_FONCTION( DFSDM1_FLT1_Handler);
// MA_FONCTION( DFSDM1_FLT2_Handler);
// MA_FONCTION( COMP_Handler);
// MA_FONCTION( LPTIM1_Handler);   
// MA_FONCTION( LPTIM2_Handler);
// MA_FONCTION( OTG_FS_Handler);
// MA_FONCTION( DMA2_Channel6_Handler);
// MA_FONCTION( DMA2_Channel7_Handler);
// MA_FONCTION( LPUART1_Handler);
// MA_FONCTION( QUADSPI_Handler);
// MA_FONCTION( I2C3_EV_Handler);
// MA_FONCTION( I2C3_ER_Handler);
// MA_FONCTION( SAI1_Handler);
// MA_FONCTION( SAI2_Handler);
// MA_FONCTION( SWPMI1_Handler);
// MA_FONCTION( TSC_Handler);
// MA_FONCTION( RNG_Handler);
// MA_FONCTION( FPU_Handler);


// //void NonMaskableInt_Handler __attribute__((weak, alias("default_handler")));
// //void HardFault_Handler __attribute__((weak, alias("default_handler")));


// uint32_t __attribute__ ((section(".isr_vector"))) vectors[] ={
//     START_STACK,
//     (uint32_t) Reset_handler,
//     (uint32_t) NonMaskableInt_Handler,
//     (uint32_t) HardFault_Handler,
//     (uint32_t) MemoryManagement_Handler,
//     (uint32_t) BusFault_Handler,
//     (uint32_t) UsageFault_Handler,
//     (uint32_t) SVCall_Handler,
//     (uint32_t) DebugMonitor_Handler,
//     (uint32_t) PendSV_Handler,
//     (uint32_t) SysTick_Handler,
//     (uint32_t) WWDG_Handler,
//     (uint32_t) PVD_PVM_Handler,
//     (uint32_t) TAMP_STAMP_Handler,
//     (uint32_t) RTC_WKUP_Handler,
//     (uint32_t) FLASH_Handler,
//     (uint32_t) RCC_Handler,
//     (uint32_t) EXTI0_Handler,
//     (uint32_t) EXTI1_Handler,
//     (uint32_t) EXTI2_Handler,
//     (uint32_t) EXTI3_Handler,
//     (uint32_t) EXTI4_Handler,
//     (uint32_t) DMA1_Channel1_Handler,
//     (uint32_t) DMA1_Channel2_Handler,
//     (uint32_t) DMA1_Channel3_Handler,
//     (uint32_t) DMA1_Channel4_Handler,
//     (uint32_t) DMA1_Channel5_Handler,
//     (uint32_t) DMA1_Channel6_Handler,
//     (uint32_t) DMA1_Channel7_Handler,
//     (uint32_t) ADC1_2_Handler,
//     (uint32_t) CAN1_TX_Handler,
//     (uint32_t) CAN1_RX0_Handler,
//     (uint32_t) CAN1_RX1_Handler,
//     (uint32_t) CAN1_SCE_Handler,
//     (uint32_t) EXTI9_5_Handler,
//     (uint32_t) IM1_BRK_TIM15_Handler,
//     (uint32_t) TIM1_UP_TIM16_Handler,
//     (uint32_t) TRG_COM_TIM17_Handler,
//     (uint32_t) TIM1_CC_Handler,
//     (uint32_t) TIM2_Handler,
//     (uint32_t) TIM3_Handler,
//     (uint32_t) TIM4_Handler,
//     (uint32_t) I2C1_EV_Handler,
//     (uint32_t) I2C1_ER_Handler,
//     (uint32_t) I2C2_EV_Handler,
//     (uint32_t) I2C2_ER_Handler,
//     (uint32_t) SPI1_Handler,
//     (uint32_t) SPI2_Handler,
//     (uint32_t) USART1_Handler,
//     (uint32_t) USART2_Handler,
//     (uint32_t) USART3_Handler,
//     (uint32_t) EXTI15_10_Handler,
//     (uint32_t) RTC_Alarm_Handler,
//     (uint32_t) DFSDM1_FLT3_Handler,
//     (uint32_t) TIM8_BRK_Handler,
//     (uint32_t) TIM8_UP_Handler,
//     (uint32_t) TIM8_TRG_COM_Handler,
//     (uint32_t) TIM8_CC_Handler,
//     (uint32_t) ADC3_Handler,
//     (uint32_t) FMC_Handler,
//     (uint32_t) SDMMC1_Handler,
//     (uint32_t) TIM5_Handler,
//     (uint32_t) SPI3_Handler,
//     (uint32_t) UART4_Handler,
//     (uint32_t) UART5_Handler,
//     (uint32_t) TIM6_DAC_Handler,
//     (uint32_t) TIM7_Handler,
//     (uint32_t) DMA2_Channel1_Handler,
//     (uint32_t) DMA2_Channel2_Handler,
//     (uint32_t) DMA2_Channel3_Handler,
//     (uint32_t) DMA2_Channel4_Handler,
//     (uint32_t) DMA2_Channel5_Handler,
//     (uint32_t) DFSDM1_FLT0_Handler,
//     (uint32_t) DFSDM1_FLT1_Handler,
//     (uint32_t) DFSDM1_FLT2_Handler,
//     (uint32_t) COMP_Handler,
//     (uint32_t) LPTIM1_Handler,
//     (uint32_t) LPTIM2_Handler,
//     (uint32_t) OTG_FS_Handler,
//     (uint32_t) DMA2_Channel6_Handler,
//     (uint32_t) DMA2_Channel7_Handler,
//     (uint32_t) LPUART1_Handler,
//     (uint32_t) QUADSPI_Handler,
//     (uint32_t) I2C3_EV_Handler,
//     (uint32_t) I2C3_ER_Handler,
//     (uint32_t) SAI1_Handler,
//     (uint32_t) SAI2_Handler,
//     (uint32_t) SWPMI1_Handler,
//     (uint32_t) TSC_Handler,
//     (uint32_t) RNG_Handler,
//     (uint32_t) FPU_Handler
// };
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


void default_handler(){
    for(;;);
}
