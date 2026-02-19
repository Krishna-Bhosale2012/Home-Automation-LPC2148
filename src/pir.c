#include <lpc214x.h>
#include "pir.h"

#define PIR_PIN     (1<<24)
#define PIR_RELAY   (1<<25)

volatile unsigned char pir_detected = 0;

void PIR_ISR(void) __irq {
    pir_detected = 1;
    EXTINT |= (1<<2);
    VICVectAddr = 0;
}

void PIR_init(void) {

    IODIR1 |= PIR_RELAY;
    IODIR1 &= ~PIR_PIN;

    PINSEL1 |= (1<<16);   // P1.24 -> EINT2
    EXTMODE |= (1<<2);
    EXTPOLAR |= (1<<2);

    VICVectCntl0 = 0x20 | 16;
    VICVectAddr0 = (unsigned long)PIR_ISR;
    VICIntEnable |= (1<<16);
}
