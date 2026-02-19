#include <lpc214x.h>
#include "delay.h"

void delay_us(uint32_t us) {
    uint32_t i, j;
    for (i = 0; i < us; i++)
        for (j = 0; j < 10; j++);
}

void delay_ms(uint32_t ms) {
    while (ms--) delay_us(1000);
}
