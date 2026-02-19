#include <lpc214x.h>
#include <stdio.h>

#include "uart.h"
#include "lcd.h"
#include "dht11.h"
#include "pir.h"
#include "delay.h"

#define PIR_RELAY   (1<<25)

volatile unsigned char manual_override = 0;

int temperature = 0;
int humidity = 0;
char uart_buf[32];

int main(void) {

    UART1_init();
    lcd_init();
    PIR_init();

    lcd_print("System Ready");

    while (1) {

        /* UART RX */
        if (UART1_rx_available()) {
            char c = UART1_rx();
            if (c == 'y') manual_override = 1;
            if (c == 'n') manual_override = 0;
        }

        /* Read DHT */
        delay_ms(1500);
        dht11_read(&humidity, &temperature);

        /* LCD Update */
        lcd_cmd(0x01);
        lcd_print("T:");
        sprintf(uart_buf, "%d", temperature);
        lcd_print(uart_buf);

        lcd_print(" H:");
        sprintf(uart_buf, "%d", humidity);
        lcd_print(uart_buf);

        /* UART TX */
        sprintf(uart_buf, "#h:%dt:%d$", humidity, temperature);
        UART1_tx_string(uart_buf);

        /* Relay Logic */
        if (manual_override || pir_detected)
            IOSET1 |= PIR_RELAY;
        else
            IOCLR1 |= PIR_RELAY;

        pir_detected = 0;
    }
}
