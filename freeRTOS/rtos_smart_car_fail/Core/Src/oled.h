#include <stdint.h>
#ifndef _OLED_H_
#define _OLED_H_

void oled_init(void);

void oled_clear_all(void);

void oled_clear(uint8_t x0, uint8_t x1, uint8_t y0, uint8_t y1);

void old__clear_top_half(void);

void old__clear_bottom_half(void);

void oled_clear_1_line(void);

void oled_clear_2_line(void);

void oled_clear_3_line(void);

void oled_clear_4_line(void);

void oled_show_string(char row,char col,char *str);

void scroll_horizonal_page0(void);

#endif
