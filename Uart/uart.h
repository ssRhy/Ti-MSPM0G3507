#ifndef __UART_H__
#define __UART_H__

void Uartinit(void);
void uart0_send_char(char ch);
void uart0_send_string(const char* str);
void uart0_printf(const char* fmt, ...);
void uart0_send_speed(float speed);
void uart0_send_float(float val);
void uart0_send_vofa(void);

#endif