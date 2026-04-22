#include "ti_msp_dl_config.h"
#include "graph.h"
#include "Motor/motor.h"
#include "Uart/uart.h"
#include "Encoder/Encoder.h"

volatile uint32_t g_systick_count   = 0;
volatile uint32_t g_uart_tx_ticks   = 0;
volatile uint32_t g_measure_ticks  = 0;

void SysTick_Handler(void)
{
    g_systick_count++;
    if (g_uart_tx_ticks < 0xFFFFFFFF)  g_uart_tx_ticks++;
    if (g_measure_ticks < 0xFFFFFFFF)  g_measure_ticks++;
}

int main(void)
{
    SYSCFG_DL_init();
    uart0_send_string("[1] SYSCFG done\r\n");

    delay_cycles(1000);
    uart0_send_string("[2] delay done\r\n");

    Uartinit();
    uart0_send_string("[3] Uartinit done\r\n");

    volatile uint32_t d = 0;
    for (d = 0; d < 100000; d++) {}
    uart0_send_string("[4] post-init delay done\r\n");

    GRAPH_SENSOR_Init();
    uart0_send_string("[5] GRAPH done\r\n");

    DL_GPIO_clearInterruptStatus(GPIOB, 0xFFFFFFFF);
    NVIC_ClearPendingIRQ(GPIOB_INT_IRQn);
    NVIC_EnableIRQ(GPIOB_INT_IRQn);
    uart0_send_string("[6] NVIC enabled\r\n");

    uart0_send_string("[7] SysTick started\r\n");

    while (1) {
        if (g_measure_ticks >= 1) {
            g_measure_ticks = 0;
            MEASURE_MOTORS_SPEED();
        }

        if (g_uart_tx_ticks >= 10) {
            g_uart_tx_ticks = 0;
            uart0_send_string("TICK:");
            uart0_send_speed((float)g_systick_count);
            uart0_send_string(" M1:");
            uart0_send_speed(Motor1_Speed);
            uart0_send_string(" M2:");
            uart0_send_speed(Motor2_Speed);
            uart0_send_string("\r\n");
        }

        uint8_t s1 = !READ_HW_OUT_1;
        uint8_t s2 = !READ_HW_OUT_2;
        uint8_t s3 = !READ_HW_OUT_3;
        uint8_t s4 = !READ_HW_OUT_4;

        if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1) {
            SetSpeed(0, 0);
        } else if (s1 == 1 && s2 == 0 && s3 == 1 && s4 == 1) {
            SetSpeed(0.5, 2);
        } else if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1) {
            SetSpeed(0.5, 2.5);
        } else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 1) {
            SetSpeed(2, 0.5);
        } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 0) {
            SetSpeed(2.5, 0.5);
        } else {
            SetSpeed(1, 1);
        }
    }
}
