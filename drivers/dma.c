
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

uint16_t buffer[CHUNK_SIZE];

void dam_config(){
    if(RCC == NULL || DMA1 == NULL )return; 

    //enable clock of DMA
    RCC->AHB1ENR |= (RCC_AHB1ENR_DMA1EN);

    //configuratoin of DMA
    *DMA1_CSELR             &=  ~(0xFU<<8);
    DMA1_Channel3->CPAR     =   &(SPI1->DR);
    DMA1_Channel3->CMAR     =   (buffer);

    DMA1_Channel3->CCR      &=  ~(0x3U<<12); //Priority level reset 
    DMA1_Channel3->CCR      |=  (0x1U<<12); //Set priority medium
    
    DMA1_Channel3->CCR      |= (0x1U<<4); //Set data direction

    DMA1_Channel3->CCR      |= (0x1U<<7); //Set 1 in bit 7 to enable MINC

    DMA1_Channel3->CCR      &= ~(0x3U<<8); //PSIZE 8 bits
    DMA1_Channel3->CCR      &= ~(0x3U<<10); //MSIZE 8 bits

    DMA1_Channel3->CCR      |= (0x1U<<3); //transfert error enable
    DMA1_Channel3->CCR      |= (0x1U<<2); // half transfert enable
    DMA1_Channel3->CCR      |= (0x1U<<1); //complet transfert enable



}


void dma_send_data(uint16_t size){
    DMA1_Channel3->CNDTR = size;
}