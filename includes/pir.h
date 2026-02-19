#ifndef PIR_H
#define PIR_H

extern volatile unsigned char pir_detected;

void PIR_init(void);
void PIR_ISR(void) __irq;

#endif
