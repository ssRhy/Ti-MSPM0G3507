/*
 * Encoder.c — 双电机（左右轮）正交编码器速度测量
 *
 * MSPM0G3507: GPIOB 中断经 GROUP1 分组路由
 * 所有 GPIO 端口的中断合并到 GROUP0 / GROUP1，入口是 GROUP1_IRQHandler
 *
 * 使用方法：
 * 1. 在 ti_msp_dl_config.h 中定义 Encoder_PORT 和各相引脚宏
 * 2. 在 main() 中调用 NVIC_EnableIRQ(GROUP1_INT_IRQn) 使能 GROUP1 中断
 * 3. Motor1_Encoder_Value / Motor2_Encoder_Value 为累计编码器脉冲数（持续累加，不清零）
 * 4. 定时调用 MEASURE_MOTORS_SPEED() 计算 Motor1_Speed / Motor2_Speed（m/s）
 */

#include "Encoder.h"

int32_t Motor1_Encoder_Value = 0;
int32_t Motor2_Encoder_Value = 0;

static int32_t Motor1_Encoder_Last = 0;
static int32_t Motor2_Encoder_Last = 0;

float Motor1_Speed = 0;
float Motor2_Speed = 0;

// 每200ms的新增脉冲数（用于PID控制）
int32_t Motor1_Encoder_Delta = 0;
int32_t Motor2_Encoder_Delta = 0;

void GROUP1_IRQHandler(void)
{
    if (DL_Interrupt_getStatusGroup(DL_INTERRUPT_GROUP_1, DL_INTERRUPT_GROUP1_GPIOB))
    {
        uint32_t stat = DL_GPIO_getEnabledInterruptStatus(
            Encoder_PORT,
            Encoder_A_PIN | Encoder_B_PIN | Encoder_C_PIN | Encoder_D_PIN);

        if (stat & Encoder_A_PIN) {
            DL_GPIO_clearInterruptStatus(Encoder_PORT, Encoder_A_PIN);
            if (Read_Encoder_A == 1) {
                Motor1_Encoder_Value += (Read_Encoder_B == 0) ? 1 : -1;
            } else {
                Motor1_Encoder_Value += (Read_Encoder_B == 0) ? -1 : 1;
            }
        }

        if (stat & Encoder_B_PIN) {
            DL_GPIO_clearInterruptStatus(Encoder_PORT, Encoder_B_PIN);
            if (Read_Encoder_B == 1) {
                Motor1_Encoder_Value += (Read_Encoder_A == 0) ? -1 : 1;
            } else {
                Motor1_Encoder_Value += (Read_Encoder_A == 0) ? 1 : -1;
            }
        }

        if (stat & Encoder_C_PIN) {
            DL_GPIO_clearInterruptStatus(Encoder_PORT, Encoder_C_PIN);
            if (Read_Encoder_C == 1) {
                Motor2_Encoder_Value += (Read_Encoder_D == 0) ? 1 : -1;
            } else {
                Motor2_Encoder_Value += (Read_Encoder_D == 0) ? -1 : 1;
            }
        }

        if (stat & Encoder_D_PIN) {
            DL_GPIO_clearInterruptStatus(Encoder_PORT, Encoder_D_PIN);
            if (Read_Encoder_D == 1) {
                Motor2_Encoder_Value += (Read_Encoder_C == 0) ? -1 : 1;
            } else {
                Motor2_Encoder_Value += (Read_Encoder_C == 0) ? 1 : -1;
            }
        }
    }
}

void Motor1_Get_Speed(void)
{
    int32_t delta = Motor1_Encoder_Value - Motor1_Encoder_Last;
    Motor1_Encoder_Last = Motor1_Encoder_Value;
    Motor1_Speed = (float)delta / (CC) * 2.0f * PI * RR / SAMPLE_TIME;
}

void Motor2_Get_Speed(void)
{
    int32_t delta = Motor2_Encoder_Value - Motor2_Encoder_Last;
    Motor2_Encoder_Last = Motor2_Encoder_Value;
    Motor2_Speed = -(float)delta / (CC) * 2.0f * PI * RR / SAMPLE_TIME;
}

float Motor1_Lucheng = 0;
float Motor2_Lucheng = 0;
float Measure_Distance = 0;

void MEASURE_MOTORS_SPEED(void)
{
    // 计算每200ms的脉冲增量（用于PID控制）
    Motor1_Encoder_Delta = Motor1_Encoder_Value - Motor1_Encoder_Last;
    Motor2_Encoder_Delta = Motor2_Encoder_Value - Motor2_Encoder_Last;
    Motor1_Encoder_Last = Motor1_Encoder_Value;
    Motor2_Encoder_Last = Motor2_Encoder_Value;

    // 计算速度（m/s）
    Motor1_Speed = (float)Motor1_Encoder_Delta / (CC) * 2.0f * PI * RR / SAMPLE_TIME;
    Motor2_Speed = -(float)Motor2_Encoder_Delta / (CC) * 2.0f * PI * RR / SAMPLE_TIME;

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
