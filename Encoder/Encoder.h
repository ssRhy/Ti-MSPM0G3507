#ifndef __ENCODER_H__
#define __ENCODER_H__

// === 引入 MSP 驱动库类型 ===
#include "ti_msp_dl_config.h"

// === 编码器 GPIO 宏（直接映射到 SysConfig 生成的宏名） ===
#define Encoder_PORT         GPIOB
#define Encoder_A_PIN        DL_GPIO_PIN_17   // GPIOB.17，左轮 A 相
#define Encoder_B_PIN        DL_GPIO_PIN_18   // GPIOB.18，左轮 B 相
#define Encoder_C_PIN        DL_GPIO_PIN_20   // GPIOB.20，右轮 A 相
#define Encoder_D_PIN        DL_GPIO_PIN_19   // GPIOB.19，右轮 B 相

// === 电机物理参数（请根据实际情况修改） ===




#define ENCODE_13X   11      // 编码器线数（每转脉冲数）
#define JIANSUBI     9.6      // 减速比（如 20:1 减速箱）
#define BEIPIN       4       // 4倍频（软件四分频）
#define CC           (ENCODE_13X * JIANSUBI * BEIPIN)  // 每转总脉冲数
#define SAMPLE_TIME  0.2    // 速度采样周期，单位秒（与 main 中 200ms 调用间隔一致）

#define PI  3.1415f
#define RR  12.5f            // 轮子半径，单位 mm

// === 读取编码器引脚状态（返回 0=高电平，1=低电平） ===
#define Read_Encoder_A   (DL_GPIO_readPins(Encoder_PORT,Encoder_A_PIN)==Encoder_A_PIN)?0:1  // 左轮 A相
#define Read_Encoder_B   (DL_GPIO_readPins(Encoder_PORT,Encoder_B_PIN)==Encoder_B_PIN)?0:1  // 左轮 B相
#define Read_Encoder_C   (DL_GPIO_readPins(Encoder_PORT,Encoder_C_PIN)==Encoder_C_PIN)?0:1  // 右轮 A相
#define Read_Encoder_D   (DL_GPIO_readPins(Encoder_PORT,Encoder_D_PIN)==Encoder_D_PIN)?0:1  // 右轮 B相

extern int32_t Motor1_Encoder_Value;
extern int32_t Motor2_Encoder_Value;
extern int32_t Motor1_Encoder_Delta;  // 每200ms的脉冲增量
extern int32_t Motor2_Encoder_Delta;
extern float Motor1_Speed;
extern float Motor2_Speed;
extern float Measure_Distance;

void Motor1_Get_Speed(void);
void Motor2_Get_Speed(void);
void MEASURE_MOTORS_SPEED(void);

#endif
