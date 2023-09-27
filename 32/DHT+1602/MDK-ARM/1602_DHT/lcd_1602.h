#include "gpio.h"

#ifndef _LCD1602_H_
#define _LCD1602_H_

void write_data(char d);

void write_cmd(char cmd);

void lcd_1602_init(void);

void show_line(char row, char col, char *string);

#endif
