/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 */

 /******************** (C) COPYRIGHT 2025   B站：电子大师兄 ****************************
* 文件名    : empty.c
* 作者      : 电子大师兄（https://space.bilibili.com/568487373）
* 版本      : V1.0
* 时间      : 2025-6-6
* 描述      : 主逻辑文件
*******************************************************************************/



/*******************************************************************************
* 函数名 : TT_Moto2
* 描述    : TT电机控制函数
* 作者    : 电子大师兄
* 输入    : dir=0，停止；dir=1，正转；dir=2，反转
*           pwm，取值范围0~3200，对应占空比0%~100%，对应转速从0到最大值
* 输出    : None
* 返回    : None
*******************************************************************************/
#include "ti_msp_dl_config.h"
#include "Motor/motor.h"



int main(void)
{
    SYSCFG_DL_init();

    //启动定时器G0
    DL_TimerG_startCounter(TB6612_PWM_INST);

    while (1) {
          //TT电机控制函数，控制电机的方向由g_dir决定，控制电机的转速由g_pwm决定
          TT_Moto1(&g_dir1,&g_pwm1); 
          TT_Moto2(&g_dir2,&g_pwm2); 
          //延时1秒
          delay_cycles(CPUCLK_FREQ);
    }
}
