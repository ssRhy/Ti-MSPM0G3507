#include "pid.h"
#include "ti_msp_dl_config.h"

// 电机速度 PID
PID_TypeDef pid_motor1;
PID_TypeDef pid_motor2;

// 偏航角 PID（用于出弯直行修正）
PID_TypeDef pid_yaw;

// ============ 出弯修正相关变量 ============
extern float yaw;  // MPU6050的yaw角

// 出弯修正状态
static Curve_State_TypeDef g_curve_state = CURVE_STATE_STRAIGHT;
static float g_yaw_at_curve_start = 0.0f;  // 入弯时的yaw基准
static float g_yaw_at_curve_exit = 0.0f;    // 出弯时的yaw基准
static uint32_t g_exit_start_time = 0;      // 出弯开始时间
static uint8_t g_prev_edge_sensor = 0;     // 上一时刻是否有边缘传感器检测到黑线

// 出弯修正参数
#define YAW_CORRECT_KP       1.5f    // P控制系数：yaw偏差1度，PWM修正1.5
#define YAW_CORRECT_MAX      15      // 最大修正PWM
#define YAW_CORRECT_TIMEOUT  300     // 出弯修正超时时间(ms)
#define YAW_CORRECT_MIN_TIME 150     // 出弯修正最短时间(ms)

// 判断是否是边缘传感器(大弯转角)
#define IS_EDGE_SENSOR(s1, s8)  ((s1 == 0) || (s8 == 0))
// 判断是否在弯道中
#define IS_IN_CURVE(s1, s8)     (IS_EDGE_SENSOR(s1, s8))

extern uint32_t get_system_time_ms(void);

void Curve_Tracker_Update(uint8_t s1, uint8_t s8, uint8_t s4, uint8_t s5, uint32_t current_time)
{
    uint8_t current_edge = IS_EDGE_SENSOR(s1, s8);
    uint8_t current_straight = (s4 == 0) || (s5 == 0);

    switch (g_curve_state) {
        case CURVE_STATE_STRAIGHT:
            if (current_edge) {
                g_curve_state = CURVE_STATE_IN_CURVE;
                g_yaw_at_curve_start = yaw;
            }
            break;

        case CURVE_STATE_IN_CURVE:
            if (current_edge && !g_prev_edge_sensor) {
                // 弯道中保持基准
            } else if (!current_edge && current_straight) {
                // 出弯！检测到直线但没有边缘传感器
                g_curve_state = CURVE_STATE_EXITING;
                g_yaw_at_curve_exit = yaw;
                g_exit_start_time = current_time;
            }
            break;

        case CURVE_STATE_EXITING:
            if (current_edge) {
                // 又检测到弯道，返回弯道状态
                g_curve_state = CURVE_STATE_IN_CURVE;
                g_yaw_at_curve_start = yaw;
            } else if (!current_straight) {
                // 修正超时或再次全白，回到直道
                g_curve_state = CURVE_STATE_STRAIGHT;
            }
            break;
    }

    g_prev_edge_sensor = current_edge;
}

float Curve_Tracker_Get_Correction(void)
{
    if (g_curve_state != CURVE_STATE_EXITING) {
        return 0.0f;
    }

    uint32_t elapsed = get_system_time_ms() - g_exit_start_time;

    // 超时则停止修正
    if (elapsed > YAW_CORRECT_TIMEOUT) {
        g_curve_state = CURVE_STATE_STRAIGHT;
        return 0.0f;
    }

    // 基于出弯时的yaw与当前yaw的偏差计算修正量
    // 正值表示需要左偏（向右修正），负值表示需要右偏（向左修正）
    float yaw_error = g_yaw_at_curve_exit - yaw;

    // 限幅
    float max_error = YAW_CORRECT_MAX / YAW_CORRECT_KP;
    if (yaw_error > max_error) yaw_error = max_error;
    if (yaw_error < -max_error) yaw_error = -max_error;

    return YAW_CORRECT_KP * yaw_error;
}

uint8_t Curve_Tracker_Is_Exiting(void)
{
    return (g_curve_state == CURVE_STATE_EXITING);
}

void Curve_Tracker_Reset(void)
{
    g_curve_state = CURVE_STATE_STRAIGHT;
    g_prev_edge_sensor = 0;
}

/**
 * @brief PID 参数初始化
 */
void PID_Init(PID_TypeDef *pid, float p, float i, float d, float max, float min, float imax)
{
    pid->Kp = p;
    pid->Ki = i;
    pid->Kd = d;
    pid->out_max = max;
    pid->out_min = min;
    pid->i_max = imax;
}

void PID_Clear(PID_TypeDef *pid)
{
    pid->target = 0;
    pid->actual = 0;
    pid->err = 0;
    pid->err_last = 0;
    pid->err_last_last = 0;
    pid->integral = 0;
    pid->output = 0;
}

/**
 * @brief 位置式 PID 计算
 */
float PID_Calc_Positional(PID_TypeDef *pid, float actual)
{
    pid->actual = actual;
    pid->err = pid->target - actual;
    
    // 积分累加
    pid->integral += pid->err;
    
    // 积分限幅 (抗饱和)
    if (pid->integral > pid->i_max) pid->integral = pid->i_max;
    if (pid->integral < -pid->i_max) pid->integral = -pid->i_max;
    
    // 计算输出
    pid->output = pid->Kp * pid->err + 
                  pid->Ki * pid->integral + 
                  pid->Kd * (pid->err - pid->err_last);
                  
    pid->err_last = pid->err;
    
    // 输出限幅
    if (pid->output > pid->out_max) pid->output = pid->out_max;
    if (pid->output < pid->out_min) pid->output = pid->out_min;
    
    return pid->output;
}

/**
 * @brief 增量式 PID 计算
 * Δu = Kp*(e[k]-e[k-1]) + Ki*e[k] + Kd*(e[k]-2*e[k-1]+e[k-2])
 */
float PID_Calc_Incremental(PID_TypeDef *pid, float actual)
{
    pid->actual = actual;
    float err = pid->target - actual;

    float delta_output = pid->Kp * (err - pid->err_last)
                       + pid->Ki * err
                       + pid->Kd * (err - 2 * pid->err_last + pid->err_last_last);

    pid->output += delta_output;

    pid->err_last_last = pid->err_last;
    pid->err_last = err;

    // 输出限幅
    if (pid->output > pid->out_max) pid->output = pid->out_max;
    if (pid->output < pid->out_min) pid->output = pid->out_min;

    return pid->output;
}

