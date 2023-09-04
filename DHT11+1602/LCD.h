#ifndef _LCD_H_
#define _LCD_H_

void busy_check();
void write_cmd(char cmd);
void write_data(char d);
void lcd_init();
#endif