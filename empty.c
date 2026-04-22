#include "ti/driverlib/dl_timerg.h"
#include "ti_msp_dl_config.h"
#include "graph.h"
#include "Motor/motor.h"
#include "Uart/uart.h"
#include "Encoder/Encoder.h"
#include "clock/clock.h"


int main(void)
{
    SYSCFG_DL_init();
    uart0_send_string("\r\n===== BOOT START =====\r\n");
    for (volatile uint32_t w = 0; w < 1000000; w++) {}//test
    uart0_send_string("[1] SYSCFG done\r\n");

    delay_cycles(100000);
    uart0_send_string("[2] delay done\r\n");

    Uartinit();
    uart0_send_string("[3] Uartinit done\r\n");

    volatile uint32_t d = 0;
    for (d = 0; d < 1000000; d++) {}
    uart0_send_string("[4] post-init delay done\r\n");

    GRAPH_SENSOR_Init();
    uart0_send_string("[5] GRAPH done\r\n");

    uart0_send_string("[6] NVIC enabled\r\n");
    NVIC_EnableIRQ(GPIOB_INT_IRQn);//使能编码器中断
    SysTick_Init();//使能系统滴答定时器
    uart0_send_string("[7] SysTick started\r\n");
    DL_TimerG_startCounter(TB6612_PWM_INST);//开启pwm电机
    uart0_send_string("===== BOOT END =====\r\n");

    while (1) {
        static uint32_t last_measure = 0;
        static uint32_t last_uart = 0;
        uint32_t now = tick_ms;
//encoder 采样 ms 窗口内的脉冲数
        if (now - last_measure >= 200) {
            MEASURE_MOTORS_SPEED();
            last_measure = now;
        }

        if (now - last_uart >= 500) {
            uart0_send_string("TICK:");
            uart0_send_speed((float)tick_ms);
            uart0_send_string(" M1:");
            uart0_send_speed(Motor1_Speed);
            uart0_send_string(" M2:");
            uart0_send_speed(Motor2_Speed);
            uart0_send_string("\r\n");
            last_uart = now;
        }

        SetSpeed(2, 2);
        // uint8_t s1 = !READ_HW_OUT_1;
        // uint8_t s2 = !READ_HW_OUT_2;
        // uint8_t s3 = !READ_HW_OUT_3;
        // uint8_t s4 = !READ_HW_OUT_4;

        // if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1) {
        //     SetSpeed(0, 0);
        // } else if (s1 == 1 && s2 == 0 && s3 == 1 && s4 == 1) {
        //     SetSpeed(0.5, 2);
        // } else if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1) {
        //     SetSpeed(0.5, 2.5);
        // } else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 1) {
        //     SetSpeed(2, 0.5);
        // } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 0) {
        //     SetSpeed(2.5, 0.5);
        // } else {
        //     SetSpeed(1, 1);
        // }
    }
}
