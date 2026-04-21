/*
 * Encoder.c — 双电机（左右轮）正交编码器速度测量
 *
 * 使用方法：
 * 1. 在 ti_msp_dl_config.h 中定义 Encoder_PORT 和 Encoder_A_PIN ~ Encoder_D_PIN
 * 2. 在 main() 中调用 NVIC_EnableIRQ(GPIOB_INT_IRQn) 使能编码器中断（中断组根据实际GPIO端口）
 * 3. 定时调用 MEASURE_MOTORS_SPEED()， Motor1_Speed 为左轮速度，Motor2_Speed 为右轮速度
 *
 * 速度单位为 cm/s（需根据实际轮子半径修改 Encoder.h 中的 RR 参数）
 */

#include "Encoder.h"

int32_t Motor1_Encoder_Value = 0;  // 左轮编码器计数值
int32_t Motor2_Encoder_Value = 0;  // 右轮编码器计数值

float Motor1_Speed = 0;  // 左轮速度 cm/s
float Motor2_Speed = 0;  // 右轮速度 cm/s

// 左轮编码器中断处理（A相 / B相）
void GROUP1_IRQHandler(void)
{
    if (DL_Interrupt_getStatusGroup(DL_INTERRUPT_GROUP_1, DL_INTERRUPT_GROUP1_GPIOB))
    {
        uint32_t Encoder_GPIO_Int =
            DL_GPIO_getEnabledInterruptStatus(Encoder_PORT, Encoder_A_PIN | Encoder_B_PIN | Encoder_C_PIN | Encoder_D_PIN);

        // 左轮 A相
        if ((Encoder_GPIO_Int & Encoder_A_PIN) == Encoder_A_PIN)
        {
            DL_GPIO_clearInterruptStatus(Encoder_PORT, Encoder_A_PIN);
            if (Read_Encoder_A == 1)
            { // 上升沿
                if (Read_Encoder_B == 0)
                    Motor1_Encoder_Value++;
                else if (Read_Encoder_B == 1)
                    Motor1_Encoder_Value--;
            }
            else
            { // 下降沿
                if (Read_Encoder_B == 0)
                    Motor1_Encoder_Value--;
                else if (Read_Encoder_B == 1)
                    Motor1_Encoder_Value++;
            }
        }

        // 左轮 B相
        if ((Encoder_GPIO_Int & Encoder_B_PIN) == Encoder_B_PIN)
        {
            DL_GPIO_clearInterruptStatus(Encoder_PORT, Encoder_B_PIN);
            if (Read_Encoder_B == 1)
            { // 上升沿
                if (Read_Encoder_A == 0)
                    Motor1_Encoder_Value--;
                else if (Read_Encoder_A == 1)
                    Motor1_Encoder_Value++;
            }
            else
            { // 下降沿
                if (Read_Encoder_A == 0)
                    Motor1_Encoder_Value++;
                else if (Read_Encoder_A == 1)
                    Motor1_Encoder_Value--;
            }
        }

        // 右轮 A相
        if ((Encoder_GPIO_Int & Encoder_C_PIN) == Encoder_C_PIN)
        {
            DL_GPIO_clearInterruptStatus(Encoder_PORT, Encoder_C_PIN);
            if (Read_Encoder_C == 1)
            { // 上升沿
                if (Read_Encoder_D == 0)
                    Motor2_Encoder_Value++;
                else if (Read_Encoder_D == 1)
                    Motor2_Encoder_Value--;
            }
            else
            { // 下降沿
                if (Read_Encoder_D == 0)
                    Motor2_Encoder_Value--;
                else if (Read_Encoder_D == 1)
                    Motor2_Encoder_Value++;
            }
        }

        // 右轮 B相
        if ((Encoder_GPIO_Int & Encoder_D_PIN) == Encoder_D_PIN)
        {
            DL_GPIO_clearInterruptStatus(Encoder_PORT, Encoder_D_PIN);
            if (Read_Encoder_D == 1)
            { // 上升沿
                if (Read_Encoder_C == 0)
                    Motor2_Encoder_Value--;
                else if (Read_Encoder_C == 1)
                    Motor2_Encoder_Value++;
            }
            else
            { // 下降沿
                if (Read_Encoder_C == 0)
                    Motor2_Encoder_Value++;
                else if (Read_Encoder_C == 1)
                    Motor2_Encoder_Value--;
            }
        }
    }
}

// 左轮速度计算
void Motor1_Get_Speed(void)
{
    int32_t Encoder_TIM = Motor1_Encoder_Value;
    Motor1_Encoder_Value = 0;
    Motor1_Speed = (float)Encoder_TIM / (CC)*PI * RR;
}

// 右轮速度计算
void Motor2_Get_Speed(void)
{
    int32_t Encoder_TIM = Motor2_Encoder_Value;
    Motor2_Encoder_Value = 0;
    Motor2_Speed = -(float)Encoder_TIM / (CC)*PI * RR;
}

float Motor1_Lucheng = 0;  // 左轮累计路程 cm
float Motor2_Lucheng = 0;  // 右轮累计路程 cm
float Measure_Distance = 0;

// 更新所有电机速度及累计路程
void MEASURE_MOTORS_SPEED(void)
{
    Motor1_Get_Speed();
    Motor2_Get_Speed();

    Motor1_Lucheng += Motor1_Speed * SAMPLE_TIME;
    Motor2_Lucheng += Motor2_Speed * SAMPLE_TIME;
    Measure_Distance = (Motor1_Lucheng + Motor2_Lucheng) / 2.0f;

    if (Measure_Distance > 10000)
    {
        Measure_Distance = 0;
        Motor1_Lucheng = 0;
        Motor2_Lucheng = 0;
    }
}
