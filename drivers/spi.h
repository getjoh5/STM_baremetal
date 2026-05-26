#ifndef SPI_H
#define SPI_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Initialise le peripherique SPI1.
 */
void spi_init(void);

/**
 * @brief Transmet un buffer sur SPI1 en mode bloquant.
 */
void spi_write(const uint8_t *data, size_t len);

#endif
