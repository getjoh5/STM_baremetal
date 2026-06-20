#ifndef SPI_H
#define SPI_H

#include <stddef.h>
#include <stdint.h>

#define CHUNK_SIZE 512

extern uint16_t buffer[CHUNK_SIZE];

/**
 * @brief Initialise le peripherique SPI1.
 *
 * Configure SPI1 en transmission 8 bits et initialise le canal DMA TX associe.
 */
void spi_init(void);

/**
 * @brief Transmet un buffer sur SPI1 en mode bloquant.
 */
void spi_write(const uint8_t *data, size_t len);

/**
 * @brief Transmet un buffer 8 bits sur SPI1 avec DMA en mode bloquant.
 *
 * La fonction attend la fin du transfert DMA puis la fin physique du SPI.
 */
void spi_write_dma(const uint8_t *data, size_t len);

#endif
