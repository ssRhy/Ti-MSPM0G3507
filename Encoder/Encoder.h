#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "empty.h"

// === 电机物理参数（请根据实际情况修改） ===
#define ENCODE_13X   13      // 编码器线数（每转脉冲数）
#define JIANSUBI     20      // 减速比（如 20:1 减速箱）
#define BEIPIN       4       // 4倍频（软件四分频）
#define SAMPLE_TIME  0.01    // 速度采样周期，单位秒

#define PI  3.1415f
#define RR  20.5f            // 轮子半径，单位 cm

// === 编码器引脚定义（请在 ti_msp_dl_config.h 中配置对应 GPIO） ===
// Encoder_PORT 由 ti_msp_dl_config.h 定义
// Encoder_A_PIN, Encoder_B_PIN, Encoder_C_PIN, Encoder_D_PIN 由 ti_msp_dl_config.h 定义

#ifndef Encoder_PORT
#error "请在 ti_msp_dl_config.h 中定义 Encoder_PORT"
#endif
#ifndef Encoder_A_PIN
#error "请在 ti_msp_dl_config.h 中定义 Encoder_A_PIN (左轮A相)"
#endif
#ifndef Encoder_B_PIN
#error "请在 ti_msp_dl_config.h 中定义 Encoder_B_PIN (左轮B相)"
#endif
#ifndef Encoder_C_PIN
#error "请在 ti_msp_dl_config.h 中定义 Encoder_C_PIN (右轮A相)"
#endif
#ifndef Encoder_D_PIN
#error "请在 ti_msp_dl_config.h 中定义 Encoder_D_PIN (右轮B相)"
#endif

#define Read_Encoder_A   (DL_GPIO_readPins(Encoder_PORT,Encoder_A_PIN)==Encoder_A_PIN)?0:1  // 左轮 A相
#define Read_Encoder_B   (DL_GPIO_readPins(Encoder_PORT,Encoder_B_PIN)==Encoder_B_PIN)?0:1  // 左轮 B相
#define Read_Encoder_C   (DL_GPIO_readPins(Encoder_PORT,Encoder_C_PIN)==Encoder_C_PIN)?0:1  // 右轮 A相
#define Read_Encoder_D   (DL_GPIO_readPins(Encoder_PORT,Encoder_D_PIN)==Encoder_D_PIN)?0:1  // 右轮 B相

extern int32_t Motor1_Encoder_Value;
extern int32_t Motor2_Encoder_Value;
extern float Motor1_Speed;
extern float Motor2_Speed;
extern float Measure_Distance;

void Motor1_Get_Speed(void);
void Motor2_Get_Speed(void);
void MEASURE_MOTORS_SPEED(void);

#endif
