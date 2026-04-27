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
    Motor_Init();//初始化电机


    Uartinit();
    GRAPH_SENSOR_Init();
    NVIC_EnableIRQ(GPIOB_INT_IRQn);//使能编码器中断
    SysTick_Init();//使能系统滴答定时器
    DL_TimerG_startCounter(TB6612_PWM_INST);//开启pwm电机


    // while (1) {
    //     // static uint32_t last_measure = 0;
    //     // static uint32_t last_uart = 0;
    //     // uint32_t now = tick_ms;

    //     // if (now - last_measure >= 200) {
    //     //     MEASURE_MOTORS_SPEED();
    //     //     last_measure = now;
    //     // }

    //     // if (now - last_uart >= 500) {
    //     //     uart0_send_vofa_debug();
    //     //     last_uart = now;
    //     // }

    //     // // 测试：固定速度差，左轮1.0，右轮0.5
    //     // SetSpeed(1.0, 0.5);
    //     // 测试：直接设置固定PWM，不经过PID

    // }
    while (1) {
        static uint32_t last_measure = 0;
        uint32_t now = tick_ms;
        
        if (now - last_measure >= 200) {
            MEASURE_MOTORS_SPEED();
            last_measure = now;
        }
        
        while (1) {
                    uint8_t s1 = READ_HW_OUT_1;
                    uint8_t s2 = READ_HW_OUT_2;
                    uint8_t s3 = READ_HW_OUT_3;
                    uint8_t s4 = READ_HW_OUT_4;
                    uint8_t s5 = READ_HW_OUT_5;
                    uint8_t s6 = READ_HW_OUT_6;
                    uint8_t s7 = READ_HW_OUT_7;
                    uint8_t s8 = READ_HW_OUT_8;
            
            if (s1 == 0) {
                SetSpeed(20, 100);  // 右传感器看到黑 → 右轮减速
            } else if (s8 == 0) {
                SetSpeed(100, 20);  // 左传感器看到黑 → 左轮减速
            } else {
                SetSpeed(80, 80);  // 直行
            }
        }

    //     // 调用PID，设置目标速度（mm/s）
    //     // 循迹逻辑：左边传感器检测到黑线→左转，右边检测到→右转
    //     // 原始值 × 60 = mm/s（假设原始最大值2.5对应150mm/s）
    //     uint8_t s1 = READ_HW_OUT_1;
    //     uint8_t s2 = READ_HW_OUT_2;
    //     uint8_t s3 = READ_HW_OUT_3;
    //     uint8_t s4 = READ_HW_OUT_4;
    //     uint8_t s5 = READ_HW_OUT_5;
    //     uint8_t s6 = READ_HW_OUT_6;
    //     uint8_t s7 = READ_HW_OUT_7;
    //     uint8_t s8 = READ_HW_OUT_8;
        
    //     //检测到黑色输出为0，检测到白色输出为1

    //     // 循迹逻辑：黑线=0，白线=1
    //     // 黑线在左侧则左转（减少左轮速度），黑线在右侧则右转（减少右轮速度）
    //     if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 0 && s6 == 0 && s7 == 0 && s8 == 0) {
    //         SetSpeed(0, 0); // 全黑，停止
    //     } else if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(30, 160); // 黑线在最左侧，大左转
    //     } else if (s1 == 1 && s2 == 0 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(30, 150); // 黑线在左侧2号位，左转
    //     } else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(30, 120); // 黑线在左内侧，小左转
    //     } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 0 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(30, 120); // 黑线在中心偏左，小左转
    //     } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 0 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(120, 30); // 黑线在中心偏右，小右转
    //     } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 0 && s7 == 1 && s8 == 1) {
    //         SetSpeed(120, 30); // 黑线在右内侧，小右转
    //     } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 0 && s8 == 1) {
    //         SetSpeed(150, 30); // 黑线在右侧2号位，右转
    //     } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 0) {
    //         SetSpeed(160, 30); // 黑线在最右侧，大右转
    //     } else if (s1 == 0 && s2 == 0 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(20, 160); // 黑线在左侧两个传感器，大左转
    //     } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 0 && s8 == 0) {
    //         SetSpeed(160, 20); // 黑线在右侧两个传感器，大右转
    //     } else if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 0 && s8 == 1) {
    //         SetSpeed(30, 150); // 黑线在左外+右中，左转
    //     } else if (s1 == 1 && s2 == 0 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 0) {
    //         SetSpeed(150, 30); // 黑线在左中+右外，右转
    //     } else if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 0) {
    //         SetSpeed(80, 80); // 左右外侧同时检测到黑线（弯道），减速直行
    //     } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(80, 80); // 全白，出界或未检测，减速直行
    //     } else if (s1 == 0 && s2 == 0 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 0 && s8 == 0) {
    //         SetSpeed(80, 80); // 左右双侧同时检测，十字路口直行
    //     } else if (s1 == 0 && s2 == 1 && s3 == 0 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(20, 160); // 左1和左3同时检测，极限左转
    //     } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 0 && s6 == 1 && s7 == 0 && s8 == 1) {
    //         SetSpeed(160, 20); // 右3和右1同时检测，极限右转
    //     } else if (s1 == 1 && s2 == 0 && s3 == 0 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(30, 150); // 左2和左3同时检测，大左转
    //     } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 0 && s7 == 0 && s8 == 1) {
    //         SetSpeed(150, 30); // 右2和右3同时检测，大右转
    //     } else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(20, 150); // 左3和左4同时检测，大左转
    //     } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 0 && s6 == 0 && s7 == 1 && s8 == 1) {
    //         SetSpeed(150, 20); // 右4和右5同时检测，大右转
    //     } else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 1 && s5 == 0 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(30, 120); // 左3和右4同时检测
    //     } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 0 && s5 == 1 && s6 == 0 && s7 == 1 && s8 == 1) {
    //         SetSpeed(120, 30); // 左4和右5同时检测
    //     } else if (s1 == 1 && s2 == 0 && s3 == 1 && s4 == 0 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(30, 150); // 左2和左4同时检测
    //     } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 0 && s5 == 0 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(150, 30); // 右4和右5同时检测
    //     } else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 1 && s5 == 1 && s6 == 1 && s7 == 1 && s8 == 1) {
    //         SetSpeed(10, 150); // 左123同时检测，极限左转
    //     } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 0 && s7 == 0 && s8 == 0) {
    //         SetSpeed(150, 10); // 右678同时检测，极限右转
    //     } else {
    //         SetSpeed(80, 80); // 默认中速直行
    //     }
    // }
    }

}
