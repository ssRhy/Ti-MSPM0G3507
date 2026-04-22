#include "ti_msp_dl_config.h"
#include "uart.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

void uart0_send_char(char ch);
void uart0_send_string(const char* str);
void uart0_send_speed(float speed);


volatile unsigned char uart_data = 0;

void Uartinit(void)
{

    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    uart0_send_string("uart0 start\r\n");
}

void uart0_send_char(char ch)
{
    volatile uint32_t count = 5000;
    while (count-- > 0) {
        if (DL_UART_isTXFIFOEmpty(UART_0_INST)) {
            DL_UART_Main_transmitData(UART_0_INST, ch);
            return;
        }
    }
}

void uart0_send_string(const char* str)
{
    while (*str) {
        uart0_send_char(*str);
        str++;
    }
}

void uart0_send_speed(float speed)
{
    char buf[16];
    int intPart  = (int)speed;
    int fracPart = (int)(fabsf(speed) * 100.0f) % 100;

    uart0_send_char(speed < 0 ? '-' : '+');

    buf[0] = '0' + (abs(intPart) / 100) % 10;
    buf[1] = '0' + (abs(intPart) / 10) % 10;
    buf[2] = '0' + abs(intPart) % 10;
    buf[3] = '.';
    buf[4] = '0' + fracPart / 10;
    buf[5] = '0' + fracPart % 10;
    buf[6] = '\0';

    uart0_send_string(buf);
}

void UART0_IRQHandler(void)
{
    switch (DL_UART_getPendingInterrupt(UART_0_INST)) {
        case DL_UART_IIDX_RX:
            uart_data = DL_UART_Main_receiveData(UART_0_INST);
            uart0_send_char(uart_data);
            break;
        default:
            break;
    }
}
