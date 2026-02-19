#include <lpc214x.h>
#include <stdint.h>
#include "dht11.h"
#include "delay.h"

#define DHT_PIN (1<<21)

int dht11_read(int *h, int *t) {

    uint8_t data[5] = {0};
    uint8_t i, j;

    IODIR1 |= DHT_PIN;
    IOCLR1 |= DHT_PIN;
    delay_ms(18);
    IOSET1 |= DHT_PIN;
    delay_us(30);
    IODIR1 &= ~DHT_PIN;

    delay_us(80);
    if (IOPIN1 & DHT_PIN) return -1;
    delay_us(80);

    for (j = 0; j < 5; j++) {
        for (i = 0; i < 8; i++) {
            while (!(IOPIN1 & DHT_PIN));
            delay_us(40);
            if (IOPIN1 & DHT_PIN)
                data[j] |= (1 << (7 - i));
            while (IOPIN1 & DHT_PIN);
        }
    }

    if ((data[0] + data[1] + data[2] + data[3]) != data[4])
        return -1;

    *h = data[0];
    *t = data[2];

    return 0;
}
