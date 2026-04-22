#include "ti_msp_dl_config.h"
#include <string.h>

#define UART0_MAX_SEND_LEN  240

static uint8_t USART0_TX_BUF[UART0_MAX_SEND_LEN];

volatile unsigned char uart_data = 0;

void uart0_send_char(char ch);
void uart0_send_string(const char* str);
void uart0_send_speed(float speed);

void Uartinit(void)
{
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    volatile uint32_t wait = 0;
    while (DL_UART_isBusy(UART_0_INST) == true) {
        wait++;
        if (wait > 320000) break;
    }

    uart0_send_string("1\r\n");
    uart0_send_string("uart0 start work\r\n");
}

void uart0_send_char(char ch)
{
    while (DL_UART_isBusy(UART_0_INST) == true);
    DL_UART_Main_transmitData(UART_0_INST, ch);
}

void uart0_send_string(const char* str)
{
    int len = 0;
    while (str[len] != '\0') len++;

    for (int j = 0; j < len; j++) {
        while (DL_UART_isBusy(UART_0_INST) == true);
        DL_UART_Main_transmitData(UART_0_INST, str[j]);
    }
}

void uart0_send_speed(float speed)
{
    char buf[16];
    int intPart   = (int)speed;
    int fracPart  = (int)(fabsf(speed) * 100.0f) % 100;

    if (speed < 0)
        uart0_send_char('-');
    else
        uart0_send_char('+');

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
    switch (DL_UART_getPendingInterrupt(UART_0_INST))
    {
        case DL_UART_IIDX_RX:
            uart_data = DL_UART_Main_receiveData(UART_0_INST);
            uart0_send_char(uart_data);
            break;
        default:
            break;
    }
}
