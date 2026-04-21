#include "motor.h"

uint8_t g_dir1 =DIR_BACKWARD;
uint32_t g_pwm1 = 1600;

uint8_t g_dir2 = DIR_BACKWARD;
uint32_t g_pwm2 = 1600;


/*******************************************************************************
* 函数名 : TT_Moto1
* 描述    : TT电机控制函数
* 作者    : 电子大师兄
* 输入    : dir=0，停止；dir=1，正转；dir=2，反转
*           pwm，取值范围0~3200，对应占空比0%~100%，对应转速从0到最大值
* 输出    : None
* 返回    : None
*******************************************************************************/
void TT_Moto1(uint8_t *dir, uint32_t *pwm)
{
    //限制PWM值在合理范围内
    LIMIT(0, *pwm, MAX_PWM);

    if(DIR_FORWARD == *dir)  //正转
    {
        DL_GPIO_setPins(TB6612_IO_PORT,TB6612_IO_AIN1_PIN);
        DL_GPIO_clearPins(TB6612_IO_PORT,TB6612_IO_AIN2_PIN);
    } 
    else if(DIR_BACKWARD == *dir)   //反转
    {
        DL_GPIO_setPins(TB6612_IO_PORT,TB6612_IO_AIN2_PIN);
        DL_GPIO_clearPins(TB6612_IO_PORT,TB6612_IO_AIN1_PIN);
    }  
    else   //停止
    {
        DL_GPIO_clearPins(TB6612_IO_PORT,TB6612_IO_AIN1_PIN);
        DL_GPIO_clearPins(TB6612_IO_PORT,TB6612_IO_AIN2_PIN);

        *pwm = 0;
    }
    
    //设置比较值（决定占空比是多少）
    DL_TimerG_setCaptureCompareValue(TB6612_PWM_INST, *pwm, GPIO_TB6612_PWM_C0_IDX);
}

void TT_Moto2(uint8_t *dir, uint32_t *pwm)
{
    //限制PWM值在合理范围内
    LIMIT(0, *pwm, MAX_PWM);

    if(DIR_FORWARD == *dir)  //正转
    {
        DL_GPIO_setPins(TB6612_IO_PORT,TB6612_IO_BIN1_PIN);
        DL_GPIO_clearPins(TB6612_IO_PORT,TB6612_IO_BIN2_PIN);
    } 
    else if(DIR_BACKWARD == *dir)   //反转
    {
        DL_GPIO_setPins(TB6612_IO_PORT,TB6612_IO_BIN2_PIN);
        DL_GPIO_clearPins(TB6612_IO_PORT,TB6612_IO_BIN1_PIN);
    }  
    else   //停止
    {
        DL_GPIO_clearPins(TB6612_IO_PORT,TB6612_IO_BIN1_PIN);
        DL_GPIO_clearPins(TB6612_IO_PORT,TB6612_IO_BIN2_PIN);

        *pwm = 0;
    }
    
    //设置比较值（决定占空比是多少）
    DL_TimerG_setCaptureCompareValue(TB6612_PWM_INST, *pwm, GPIO_TB6612_PWM_C1_IDX);
}

void SetSpeed(float speed1, float speed2)
{
    g_pwm1 = (uint32_t)(speed1 / 3.0f * MAX_PWM);
    g_pwm2 = (uint32_t)(speed2 / 3.0f * MAX_PWM);
    TT_Moto1(&g_dir1, &g_pwm1);
    TT_Moto2(&g_dir2, &g_pwm2);
} 



