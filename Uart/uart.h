#ifndef __UART_H__
#define __UART_H__

#include "ti_msp_dl_config.h"

extern void Uartinit(void);
extern void uart0_send_char(char ch);
extern void uart0_send_string(char* str);
extern void UART_0_INST_IRQHandler(void);
extern volatile unsigned char uart_data;

#endif