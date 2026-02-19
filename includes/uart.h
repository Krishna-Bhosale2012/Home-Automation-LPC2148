#ifndef UART_H
#define UART_H

void UART1_init(void);
void UART1_tx(char c);
void UART1_tx_string(const char *s);
char UART1_rx_available(void);
char UART1_rx(void);

#endif
