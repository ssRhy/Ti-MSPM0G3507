#ifndef __FIFO_H__
#define __FIFO_H__

#include "ti_msp_dl_config.h"

#define 	FIFO_SIZE   128

typedef struct {
	uint16_t buffer[FIFO_SIZE];
	volatile uint8_t ptrWrite;
	volatile uint8_t ptrRead;
}FIFO_t;

extern volatile FIFO_t rxFIFO_u;
extern volatile FIFO_t rxFIFO_d;

void fifo_initQueue(void);
void fifo_enQueue(uint16_t data, uint8_t add);
uint16_t fifo_deQueue(uint8_t add);
bool fifo_isEmpty(uint8_t add);
uint16_t fifo_queueLength(uint8_t add);

#endif