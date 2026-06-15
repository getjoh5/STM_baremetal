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
#define DMA_A
#include <stdint.h>

#define CHUNK_SIZE 512
uint16_t buffer[CHUNK_SIZE];


void dam_config();



#endif