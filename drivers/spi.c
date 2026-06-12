#include "spi.h"
#include "stm32l475xx.h"

void spi_init(void){
    if(SPI1 == NULL || RCC == NULL)return;

    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    SPI1->CR1 &= ~SPI_CR1_SPE;

    //clock baudrate: slow speed for display bring-up
    SPI1->CR1 &= ~SPI_CR1_BR;
    //SPI1->CR1 |= (~(0x1U)<<SPI_CR1_BR_Pos);

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
