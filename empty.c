#include "ti_msp_dl_config.h"
#include "graph.h"
#include "Motor/motor.h"
#include "Uart/uart.h" 

int main(void)
{
    /* 1. 初始化系统时钟和外设（必须最先调用） */
    SYSCFG_DL_init();

    Uartinit();
  

    /* 2. 启动电机PWM定时器 */
    DL_TimerG_startCounter(TB6612_PWM_INST);

    /* 3. 初始化灰度传感器 */
    GRAPH_SENSOR_Init();

    while (1) {

        /* 5. 读取4路灰度传感器状态 */
        uint8_t s1 = !READ_HW_OUT_1;
        uint8_t s2 = !READ_HW_OUT_2;
        uint8_t s3 = !READ_HW_OUT_3;
        uint8_t s4 = !READ_HW_OUT_4;
        if(s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1)
        {
            SetSpeed(0, 0);
        }
        else if(s1 == 1 && s2 == 0 && s3 == 1 && s4 == 1)
        {
            SetSpeed(0.5, 2);
        }
        else if(s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1)
        {
            SetSpeed(0.5, 2.5);
        }
        else if(s1 == 1 && s2 == 1 && s3 == 0 && s4 == 1)
        {
            SetSpeed(2, 0.5);
        }
        else if(s1 == 1 && s2 == 1 && s3 == 1 && s4 == 0)
        {
            SetSpeed(2.5, 0.5);
        }
        else if(s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0)
        {
            SetSpeed(1, 1);
        }
        else
        {
            // 未精确匹配任何条件时，直行（防止电机停止）
            SetSpeed(1, 1);
        }


        // 调试：直接读取原始传感器值
    // if (!READ_HW_OUT_1 == 0) { SetSpeed(0.5, 2.5); }  // 左转
    // else { SetSpeed(2.5, 0.5); }  // 右转
            // if(READ_HW_OUT_3==1)
        // {
        //     SetSpeed(1.5,1.5);
        // }
                /* 4. 控制电机（g_dir1/g_pwm1等变量需在motor.h中定义） */
    //   if(READ_HW_OUT_4==1)
    //   {
    //      TT_Moto1(&g_dir1, &g_pwm1);
    //    TT_Moto2(&g_dir2, &g_pwm2);

    //   }
    

    }
}