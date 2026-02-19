#ifndef LCD_H
#define LCD_H

void lcd_init(void);
void lcd_cmd(unsigned char c);
void lcd_data(unsigned char d);
void lcd_print(const char *s);

#endif
