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
    Motor_Init();

    Uartinit();
    GRAPH_SENSOR_Init();
    NVIC_EnableIRQ(GPIOB_INT_IRQn);
    SysTick_Init();
    DL_TimerG_startCounter(TB6612_PWM_INST);

    while (1) {
        uint8_t s1 = READ_HW_OUT_1;
        uint8_t s2 = READ_HW_OUT_2;
        uint8_t s3 = READ_HW_OUT_3;
        uint8_t s4 = READ_HW_OUT_4;
        uint8_t s5 = READ_HW_OUT_5;
        uint8_t s6 = READ_HW_OUT_6;
        uint8_t s7 = READ_HW_OUT_7;
        uint8_t s8 = READ_HW_OUT_8;

        // 循迹逻辑：黑线=0，白线=1
        // 左转 = 左轮减速，右转 = 右轮减速

        if (s1 == 0 && s8 == 0) {
            SetSpeed(55, 30);  // 两端同时检测到黑线（弯道），直行
        }
        else if (s1 == 0) {
            SetSpeed(30, 150);  // 最左传感器看到黑 → 大左转
        }
        else if (s2 == 0) {
            SetSpeed(50, 130);  // 左2传感器看到黑 → 中左转
        }
        else if (s8 == 0) {
            SetSpeed(150, 30);  // 最右传感器看到黑 → 大右转
        }
        else if (s7 == 0) {
            SetSpeed(130, 50);  // 右2传感器看到黑 → 中右转
        }
        else if (s3 == 0) {
            SetSpeed(60, 120);  // 左3传感器看到黑 → 小左转
        }
        else if (s6 == 0) {
            SetSpeed(120, 60);  // 右3传感器看到黑 → 小右转
        }
        else if (s4 == 0 || s5 == 0) {
            SetSpeed(60, 80);   // 中间传感器看到黑 → 直行
        }
        else {
            SetSpeed(55, 30);   // 全白 → 直行
        }

     
    }
}
