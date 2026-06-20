/**
 * @file dma.h
 * @brief Interface de la dma du stm32l475.
 *
 * Ce fichier décrit l'ensemble la fonction de configuration de la dma .
 *
 * @author GWETH Christian
 * @date 2026-04-14
 */
#ifndef DMA_H
#define DMA_H
#include <stdint.h>


/**
 * @brief Configure DMA1 Channel3 pour les transmissions SPI1_TX en 8 bits.
 *
 * Cette initialisation se fait une seule fois avant les transferts.
 */
void dma_spi_tx_init(void);

/**
 * @brief Prepare un transfert DMA memoire vers SPI1->DR sans le demarrer.
 *
 * @param data Buffer source 8 bits.
 * @param size Nombre d'octets a transmettre.
 */
void dma_spi_tx_start_u8(const uint8_t *data, uint16_t size);


#endif
