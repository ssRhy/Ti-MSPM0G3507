#ifndef _CLOCK_H_
#define _CLOCK_H_

extern volatile uint32_t tick_ms;

int mspm0_delay_ms(unsigned long num_ms);
int mspm0_get_clock_ms(unsigned long *count);
void SysTick_Init(void);
uint32_t get_system_time_ms(void);

#endif  /* #ifndef _CLOCK_H_ */