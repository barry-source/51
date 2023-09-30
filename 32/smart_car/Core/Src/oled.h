#include <stdint.h>
#ifndef _OLED_H_
#define _OLED_H_

void oled_init(void);

void oled_clear(void);

void oled_show_string(char row,char col,char *str);

#endif
