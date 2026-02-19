#include <lpc214x.h>
#include "lcd.h"
#include "delay.h"

/* LCD Pins */
#define LCD_RS   (1<<13)
#define LCD_EN   (1<<16)
#define LCD_D4   (1<<17)
#define LCD_D5   (1<<18)
#define LCD_D6   (1<<19)
#define LCD_D7   (1<<20)

static void lcd_pulse(void) {
    IOSET0 |= LCD_EN;
    delay_us(40);
    IOCLR0 |= LCD_EN;
}

static void lcd_write4(unsigned char n) {

    IOCLR0 |= (LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7);

    if (n & 1) IOSET0 |= LCD_D4;
    if (n & 2) IOSET0 |= LCD_D5;
    if (n & 4) IOSET0 |= LCD_D6;
    if (n & 8) IOSET0 |= LCD_D7;

    lcd_pulse();
}

void lcd_cmd(unsigned char c) {
    IOCLR0 |= LCD_RS;
    lcd_write4(c >> 4);
    lcd_write4(c & 0x0F);
    delay_ms(2);
}

void lcd_data(unsigned char d) {
    IOSET0 |= LCD_RS;
    lcd_write4(d >> 4);
    lcd_write4(d & 0x0F);
    IOCLR0 |= LCD_RS;
}

void lcd_init(void) {

    IODIR0 |= LCD_RS | LCD_EN | LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;

    delay_ms(20);
    lcd_write4(0x03); delay_ms(5);
    lcd_write4(0x03); delay_ms(1);
    lcd_write4(0x02);

    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}

void lcd_print(const char *s) {
    while (*s) lcd_data(*s++);
}
