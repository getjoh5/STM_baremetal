#include <stdint.h>

#include "stm32l475xx.h"
#include "startup_filel.h"

/*
 * Startup minimal pour STM32L475.
 *
 * Ce fichier fournit:
 * - les handlers faibles des interruptions;
 * - la table des vecteurs placee au debut de la flash;
 * - l'initialisation de la RAM avant l'appel a main.
 */

#define WEAK_HANDLER(name)                 \
    BOOT_CODE void __attribute__((weak)) name(void)  \
    {                                      \
        __disable_irq();                   \
        default_handler();                 \
    }

/* Handlers par defaut.
 * Une application peut remplacer n'importe lequel de ces handlers en definissant
 * une fonction avec le meme nom dans un autre fichier source.
 */
WEAK_HANDLER(NonMaskableInt_Handler)
WEAK_HANDLER(HardFault_Handler)
WEAK_HANDLER(MemoryManagement_Handler)
WEAK_HANDLER(BusFault_Handler)
WEAK_HANDLER(UsageFault_Handler)
WEAK_HANDLER(SVCall_Handler)
WEAK_HANDLER(PendSV_Handler)
WEAK_HANDLER(SysTick_Handler)
WEAK_HANDLER(WWDG_Handler)
WEAK_HANDLER(PVD_PVM_Handler)
WEAK_HANDLER(TAMP_STAMP_Handler)
WEAK_HANDLER(RTC_WKUP_Handler)
WEAK_HANDLER(FLASH_Handler)
WEAK_HANDLER(RCC_Handler)
WEAK_HANDLER(EXTI0_Handler)
WEAK_HANDLER(EXTI1_Handler)
WEAK_HANDLER(EXTI2_Handler)
WEAK_HANDLER(EXTI3_Handler)
WEAK_HANDLER(EXTI4_Handler)
WEAK_HANDLER(DMA1_Channel1_Handler)
WEAK_HANDLER(DMA1_Channel2_Handler)
WEAK_HANDLER(DMA1_Channel3_Handler)
WEAK_HANDLER(DMA1_Channel4_Handler)
WEAK_HANDLER(DMA1_Channel5_Handler)
WEAK_HANDLER(DMA1_Channel6_Handler)
WEAK_HANDLER(DMA1_Channel7_Handler)
WEAK_HANDLER(ADC1_2_Handler)
WEAK_HANDLER(CAN1_TX_Handler)
WEAK_HANDLER(CAN1_RX0_Handler)
WEAK_HANDLER(CAN1_RX1_Handler)
WEAK_HANDLER(CAN1_SCE_Handler)
WEAK_HANDLER(EXTI9_5_Handler)
WEAK_HANDLER(IM1_BRK_TIM15_Handler)
WEAK_HANDLER(TIM1_UP_TIM16_Handler)
WEAK_HANDLER(TRG_COM_TIM17_Handler)
WEAK_HANDLER(TIM1_CC_Handler)
WEAK_HANDLER(TIM2_Handler)
WEAK_HANDLER(TIM3_Handler)
WEAK_HANDLER(TIM4_Handler)
WEAK_HANDLER(I2C1_EV_Handler)
WEAK_HANDLER(I2C1_ER_Handler)
WEAK_HANDLER(I2C2_EV_Handler)
WEAK_HANDLER(I2C2_ER_Handler)
WEAK_HANDLER(SPI1_Handler)
WEAK_HANDLER(SPI2_Handler)
WEAK_HANDLER(USART1_Handler)
WEAK_HANDLER(USART2_Handler)
WEAK_HANDLER(USART3_Handler)
WEAK_HANDLER(EXTI15_10_Handler)
WEAK_HANDLER(RTC_Alarm_Handler)
WEAK_HANDLER(DFSDM1_FLT3_Handler)
WEAK_HANDLER(TIM8_BRK_Handler)
WEAK_HANDLER(TIM8_UP_Handler)
WEAK_HANDLER(TIM8_TRG_COM_Handler)
WEAK_HANDLER(TIM8_CC_Handler)
WEAK_HANDLER(ADC3_Handler)
WEAK_HANDLER(FMC_Handler)
WEAK_HANDLER(SDMMC1_Handler)
WEAK_HANDLER(TIM5_Handler)
WEAK_HANDLER(SPI3_Handler)
WEAK_HANDLER(UART4_Handler)
WEAK_HANDLER(UART5_Handler)
WEAK_HANDLER(TIM6_DAC_Handler)
WEAK_HANDLER(TIM7_Handler)
WEAK_HANDLER(DMA2_Channel1_Handler)
WEAK_HANDLER(DMA2_Channel2_Handler)
WEAK_HANDLER(DMA2_Channel3_Handler)
WEAK_HANDLER(DMA2_Channel4_Handler)
WEAK_HANDLER(DMA2_Channel5_Handler)
WEAK_HANDLER(DFSDM1_FLT0_Handler)
WEAK_HANDLER(DFSDM1_FLT1_Handler)
WEAK_HANDLER(DFSDM1_FLT2_Handler)
WEAK_HANDLER(COMP_Handler)
WEAK_HANDLER(LPTIM1_Handler)
WEAK_HANDLER(LPTIM2_Handler)
WEAK_HANDLER(OTG_FS_Handler)
WEAK_HANDLER(DMA2_Channel6_Handler)
WEAK_HANDLER(DMA2_Channel7_Handler)
WEAK_HANDLER(LPUART1_Handler)
WEAK_HANDLER(QUADSPI_Handler)
WEAK_HANDLER(I2C3_EV_Handler)
WEAK_HANDLER(I2C3_ER_Handler)
WEAK_HANDLER(SAI1_Handler)
WEAK_HANDLER(SAI2_Handler)
WEAK_HANDLER(SWPMI1_Handler)
WEAK_HANDLER(TSC_Handler)
WEAK_HANDLER(RNG_Handler)
WEAK_HANDLER(FPU_Handler)

/* Table des vecteurs.
 * Le premier mot est la valeur initiale du pointeur de pile. Le deuxieme mot
 * est le point d'entree appele par le coeur apres reset.
 */
const void *const vectors[] __attribute__((section(".isr_vector"))) = {
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
    FPU_Handler,
};

static BOOT_CODE void copy_section(uint8_t *dst, const uint8_t *src, const uint8_t *end)
{
    while (dst < end) {
        *dst++ = *src++;
    }
}

static BOOT_CODE void clear_section(uint8_t *start, const uint8_t *end)
{
    while (start < end) {
        *start++ = 0;
    }
}

/* Prepare la memoire C avant l'entree dans l'application.
 * Les variables initialisees sont copiees de la flash vers .data en SRAM.
 * La section .bss est ensuite mise a zero.
 *
 * Dans ce projet, _start appelle ensuite main depuis bootloader.s.
 */
void Reset_handler(void)
{
    copy_section((uint8_t *)&_stext, (const uint8_t *)&_ld_stext, (uint8_t *)&_etext);
    copy_section((uint8_t *)&_sdata, (const uint8_t *)&_ld_sdata, (uint8_t *)&_edata);
    clear_section((uint8_t *)&_sbss, (uint8_t *)&_ebss);
}

/* Handler de secours: si une interruption non geree arrive, le programme
 * reste ici pour faciliter le diagnostic au debugger.
 */
void default_handler(void)
{
    for (;;) {
    }
}
