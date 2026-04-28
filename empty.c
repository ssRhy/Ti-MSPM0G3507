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

    uint32_t last_print_time = 0;
    uint32_t last_straight_time = 0;  // 上次检测到直行的时间
    uint8_t in_curve = 0;             // 是否刚从弯道切换过来
    int8_t last_turn_dir = 0;         // 上次转向方向：-1=左转，0=直行，1=右转

    while (1) {
        uint32_t now = get_system_time_ms();

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

        if (s1 == 0 || s8 == 0 || s2 == 0 || s7 == 0 || s3 == 0 || s6 == 0) {
            // 检测到弯道信号
            in_curve = 1;
            last_turn_dir = 0;
            last_straight_time = now;  // 重置直行计时
        }

        if (s1 == 0 && s8 == 0) {
            // 两端同时检测到黑线（弯道），直行
            in_curve = 1;
            last_turn_dir = 0;
            SetSpeed(60, 60);
        }
        else if (s1 == 0) {
            last_turn_dir = -1;  // 记录左转
            SetSpeed(30, 150);  // 最左传感器看到黑 → 大左转
        }
        else if (s2 == 0) {
            last_turn_dir = -1;  // 记录左转
            SetSpeed(60, 130);  // 左2传感器看到黑 → 中左转
        }
        else if (s8 == 0) {
            last_turn_dir = 1;   // 记录右转
            SetSpeed(150, 30);  // 最右传感器看到黑 → 大右转
        }
        else if (s7 == 0) {
            last_turn_dir = 1;   // 记录右转
            SetSpeed(130, 60);  // 右2传感器看到黑 → 中右转
        }
        else if (s3 == 0) {
            last_turn_dir = -1;  // 记录左转
            SetSpeed(40, 120);  // 左3传感器看到黑 → 小左转
        }
        else if (s6 == 0) {
            last_turn_dir = 1;   // 记录右转
            SetSpeed(120, 40);  // 右3传感器看到黑 → 小右转
        }
        else if (s4 == 0 || s5 == 0) {
            // 检测到直行区域
            if (in_curve) {
                // 刚从弯道切换过来，需要延迟
                uint32_t elapsed = now - last_straight_time;
                if (elapsed < 150) {
                    // 延迟期间保持过渡速度
                    if (last_turn_dir < 0) {
                        // 出左弯后过渡：略微左偏
                        SetSpeed(50, 80);
                    } else if (last_turn_dir > 0) {
                        // 出右弯后过渡：略微右偏
                        SetSpeed(80, 50);
                    } else {
                        // 正常过渡
                        SetSpeed(50, 80);
                    }
                } else {
                    // 延迟结束，正常直行
                    in_curve = 0;
                    last_turn_dir = 0;
                    SetSpeed(60, 60);
                }
            } else {
               
                if (s4 == 0) {
                    SetSpeed(60, 68);
                } else {
                    SetSpeed(68, 60);
                }
            }
        }
        else {
            mspm0_delay_ms(100);
            last_straight_time = now;  // 全白时也更新时间，避免误判
            if (in_curve && (now - last_straight_time < 150)) {
                // 保持过渡
                if (last_turn_dir < 0) {
                    SetSpeed(50, 80);
                } else if (last_turn_dir > 0) {
                    SetSpeed(80, 50);
                } else {
                    SetSpeed(50, 80);
                }
            } else {
                SetSpeed(60, 60);  // 全白 → 直行
                in_curve = 0;
            }
        }

        if (now - last_print_time >= 200) {
            last_print_time = now;
            MEASURE_MOTORS_SPEED();
            uart0_send_speed_debug();
        }
    }
}