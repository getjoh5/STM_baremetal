
/**
 * @file dma.c
 * @brief Implementation du driver dma pour STM32L4.
 *
 * Ce fichier contient les fonctions permettant de configurer la dma
 * en acces direct aux registres, sans utiliser
 * la HAL STM32.
 *
 * @author GWETH Christian
 * @date 2026-04-14
 */




#include "dma.h"
#include "stddef.h"
#include "stm32l4xx.h"
#include "Timer.h"

/**
 * @brief Initialise DMA1 Channel3 pour envoyer des octets vers SPI1_TX.
 */
void dma_spi_tx_init(void){
    if(RCC == NULL || DMA1 == NULL || DMA1_Channel3 == NULL)return; 

    // Enable DMA1 clock.
    RCC->AHB1ENR |= (RCC_AHB1ENR_DMA1EN);

    DMA1_Channel3->CCR      = (uint32_t)0;

    timer_delay_ms(50);

    // Select SPI1_TX request on DMA1 Channel3.
    DMA1_CSELR->CSELR       &=  ~(0xFU << DMA_CSELR_C3S_Pos);
    DMA1_CSELR->CSELR       |=  (0x1U << DMA_CSELR_C3S_Pos);

    DMA1_Channel3->CCR      &=  ~(0x3U<<12); //Priority level reset.
    DMA1_Channel3->CCR      |=  (0x1U<<12); //Set priority medium.
    
    DMA1_Channel3->CCR      |= (0x1U<<4); //Read from memory.
    DMA1_Channel3->CCR      &= ~(0x1U<<5);//Disable circular mode.

    DMA1_Channel3->CCR      |= (0x1U<<7); //Enable memory increment.

    DMA1_Channel3->CCR      &= ~(0x3U<<8); //Peripheral size: 8 bits.
    //DMA1_Channel3->CCR      |= (0x1U<<8); //PSIZE 16 bits


    DMA1_Channel3->CCR      &= ~(0x3U<<10); //Memory size: 8 bits.
    //DMA1_Channel3->CCR      |= (0x1U<<10); //MSIZE 16 bits

    DMA1_Channel3->CCR      |= (0x1U<<3); //Transfer error interrupt enable.
    DMA1_Channel3->CCR      |= (0x1U<<2); //Half transfer interrupt enable.
    DMA1_Channel3->CCR      |= (0x1U<<1); //Transfer complete interrupt enable.
}



/**
 * @brief Charge le buffer source et la taille du prochain transfert SPI DMA.
 */
void dma_spi_tx_start_u8(const uint8_t *data, uint16_t size){
    if(DMA1 == NULL || DMA1_Channel3 == NULL)return; 

    DMA1_Channel3->CCR      &= ~DMA_CCR_EN; //Disable Channel3 before reconfiguration.

    timer_delay_ms(50);

    DMA1->IFCR = DMA_IFCR_CGIF3
               | DMA_IFCR_CTCIF3
               | DMA_IFCR_CHTIF3
               | DMA_IFCR_CTEIF3;

    DMA1_Channel3->CPAR = (uint32_t)&SPI1->DR;
    DMA1_Channel3->CMAR = (uint32_t)data;
    DMA1_Channel3->CNDTR = size;
}


void dma_send_data(uint16_t size){
    DMA1_Channel3->CNDTR = size;
}
