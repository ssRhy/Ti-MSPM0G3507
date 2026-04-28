#ifndef __PID_H_
#define __PID_H_

#include "stdint.h"

// PID 控制器结构体
typedef struct
{
    float target;           // 目标值
    float actual;           // 实际值
    float err;              // 当前误差
    float err_last;         // 上一次误差
    float err_last_last;    // 上上次误差（用于增量式PID的Kd项）
    float Kp, Ki, Kd;       // PID 参数
    float integral;         // 误差积分
    float output;           // 最终输出值
    float out_max;          // 输出上限
    float out_min;          // 输出下限
    float i_max;            // 积分限幅
} PID_TypeDef;

void PID_Init(PID_TypeDef *pid, float p, float i, float d, float max, float min, float imax);
float PID_Calc_Positional(PID_TypeDef *pid, float actual);
float PID_Calc_Incremental(PID_TypeDef *pid, float actual);
void PID_Clear(PID_TypeDef *pid);

// ============ 出弯修正相关 ============
// 出弯修正状态
typedef enum {
    CURVE_STATE_STRAIGHT,   // 直道
    CURVE_STATE_IN_CURVE,   // 弯道中
    CURVE_STATE_EXITING     // 出弯修正中
} Curve_State_TypeDef;

void Curve_Tracker_Update(uint8_t s1, uint8_t s8, uint8_t s4, uint8_t s5, uint32_t current_time);
float Curve_Tracker_Get_Correction(void);
uint8_t Curve_Tracker_Is_Exiting(void);
void Curve_Tracker_Reset(void);

#endif
