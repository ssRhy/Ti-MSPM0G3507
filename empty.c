#include "ti_msp_dl_config.h"
#include "graph.h"
#include "Motor/motor.h"

int main(void)
{
    /* 1. 初始化系统时钟和外设（必须最先调用） */
    SYSCFG_DL_init();
  

    /* 2. 启动电机PWM定时器 */
    DL_TimerG_startCounter(TB6612_PWM_INST);

    /* 3. 初始化灰度传感器 */
    GRAPH_SENSOR_Init();

    while (1) {
        /* 4. 控制电机（g_dir1/g_pwm1等变量需在motor.h中定义） */
    //   if(READ_HW_OUT_4==1)
    //   {
    //      TT_Moto1(&g_dir1, &g_pwm1);
    //    TT_Moto2(&g_dir2, &g_pwm2);

    //   }
      

        /* 5. 读取4路灰度传感器状态 */
        uint8_t s1 = READ_HW_OUT_1;
        uint8_t s2 = READ_HW_OUT_2;
        uint8_t s3 = READ_HW_OUT_3;
        uint8_t s4 = READ_HW_OUT_4;
        if(READ_HW_OUT_1 == 0&&READ_HW_OUT_2 == 0&&READ_HW_OUT_3 == 0&&READ_HW_OUT_4 == 0 )
        {
            SetSpeed(1,1);
        }
        if(READ_HW_OUT_1 == 0&&READ_HW_OUT_2 == 1&&READ_HW_OUT_3 == 0&&READ_HW_OUT_4 == 0 )
        {
            SetSpeed(0.5,2);
        }
        if(READ_HW_OUT_1 == 1&&READ_HW_OUT_2 == 0&&READ_HW_OUT_3 == 0&&READ_HW_OUT_4 == 0 )
        {
        
            SetSpeed(0.5,2.5);
        }
        if(READ_HW_OUT_1 == 0&&READ_HW_OUT_2 == 0&&READ_HW_OUT_3 == 1&&READ_HW_OUT_4 == 0 )
        {
        
            SetSpeed(2,0.5);
        }
        if(READ_HW_OUT_1 == 0&&READ_HW_OUT_2 == 0&&READ_HW_OUT_3 == 0&&READ_HW_OUT_4 == 1 )
        {
    
            SetSpeed(2.5,0.5);
        }
    

        /* 6. 延时1秒（可根据需要调整） */
        delay_cycles(CPUCLK_FREQ);
    }
}