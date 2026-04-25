#include "delay.h"
#include "clock.h"

void delay_us(uint32_t us) {
    volatile uint32_t count = us * 80;
    while(count--);
}

void Tick_delay(uint32_t t) {
    uint32_t tEnd = tick_ms + t;
    while (tick_ms < tEnd);
}
