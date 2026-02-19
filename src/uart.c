#include <lpc214x.h>
#include "uart.h"

#define BAUD_DLL_9600 78   // PCLK = 12 MHz

void UART1_init(void) {
    PINSEL0 |= (1<<16) | (1<<18);   // P0.8 TXD1, P0.9 RXD1

    U1LCR = 0x83;
    U1DLL = BAUD_DLL_9600;
    U1DLM = 0x00;
    U1LCR = 0x03;
}

void UART1_tx(char c) {
    while (!(U1LSR & (1<<5)));
    U1THR = c;
}

void UART1_tx_string(const char *s) {
    while (*s) UART1_tx(*s++);
}

char UART1_rx_available(void) {
    return (U1LSR & 0x01);
}

char UART1_rx(void) {
    return U1RBR;
}
