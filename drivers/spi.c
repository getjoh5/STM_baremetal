#include "spi.h"
#include "dma.h"
#include "stm32l475xx.h"

#define DMA_MODE

uint16_t buffer[CHUNK_SIZE];

void spi_init(void){
    if(SPI1 == NULL || RCC == NULL)return;

    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    SPI1->CR1 &= ~SPI_CR1_SPE;

    //clock baudrate: slow speed for display bring-up
    SPI1->CR1 &= ~SPI_CR1_BR;
    //SPI1->CR1 |= (0x1U<<SPI_CR1_BR_Pos);//32/4 MHZ

    //configurarion CPOL CPHA
    SPI1->CR1 |= SPI_CR1_CPOL;
    SPI1->CR1 &= ~SPI_CR1_CPHA;

    //direction of transmission
    SPI1->CR1 &= ~SPI_CR1_RXONLY;
    SPI1->CR1 |= SPI_CR1_BIDIMODE;
    SPI1->CR1 |= SPI_CR1_BIDIOE;
    SPI1->CR1 |= SPI_CR1_MSTR;

    //Frame format
    SPI1->CR1 &= ~SPI_CR1_LSBFIRST;

    //SSM ss1i
    SPI1->CR1 |= SPI_CR1_SSM;
    SPI1->CR1 |= SPI_CR1_SSI;

    //DS
    SPI1->CR2 &= ~(0xFU<<SPI_CR2_DS_Pos);
    SPI1->CR2 |= (0x7U<<SPI_CR2_DS_Pos);
    SPI1->CR2 |= SPI_CR2_FRXTH;


    //Use the DMA
    //SPI1->CR2 |= SPI_CR2_TXDMAEN; //enable transmission by DMA
    dma_spi_tx_init();
    //enable SPI 
    SPI1->CR1 |= SPI_CR1_SPE;

    
}

void spi_write(const uint8_t *data, size_t len){
    if(SPI1 == NULL || data == NULL)return;



    while(len > 0U){
        while((SPI1->SR & SPI_SR_TXE) == 0U){
        }

        *((volatile uint8_t *)&SPI1->DR) = *data;
        data++;
        len--;
    }

    while((SPI1->SR & SPI_SR_BSY) != 0U){
    }

}

void spi_write_dma(const uint8_t *data, size_t len){

    if (data == NULL || len == 0U) return;
    dma_spi_tx_start_u8(data, len);
    DMA1_Channel3->CCR |= DMA_CCR_EN;

    SPI1->CR2 |= SPI_CR2_TXDMAEN;

    

    while ((DMA1->ISR & DMA_ISR_TCIF3) == 0U) {
    }

    DMA1->IFCR = DMA_IFCR_CTCIF3;

    while ((SPI1->SR & SPI_SR_BSY) != 0U) {
    }

    DMA1_Channel3->CCR &= ~DMA_CCR_EN;
    SPI1->CR2 &= ~SPI_CR2_TXDMAEN;
}
