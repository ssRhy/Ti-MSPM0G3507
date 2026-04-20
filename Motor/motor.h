#include "ti_msp_dl_config.h"

//MSPM0G3507
//参数配置：时钟32Mhz，预分频1，周期3200
//即PWM频率：32000000HZ/3200=10000HZ=10KHZ
//比较值范围：0~3200，对应占空比0%~~100%

#define MAX_PWM 3200
#define LIMIT(a, x, b)  if(x < (a))x=(a);else if(x > (b))x= (b);

#define DIR_STOP     0
#define DIR_FORWARD  1
#define DIR_BACKWARD 2

extern uint8_t g_dir1;
extern uint32_t g_pwm1;
extern uint8_t g_dir2;
extern uint32_t g_pwm2;

void TT_Moto1(uint8_t *dir, uint32_t *pwm);
void TT_Moto2(uint8_t *dir, uint32_t *pwm);
void SetSpeed(float speed1, float speed2);