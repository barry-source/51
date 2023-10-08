#include "oled.h"
#include "cmsis_os.h"

#ifndef _CARFUNCTION_H_
#define _CARFUNCTION_H_

//ËÙ¶È
extern unsigned int speedCnt;
extern char speedString[24];

void follow(void);

void avoid(void);

void traceing(void);

void stop_car(void);

void gesture(void);

void test(void);

void display_temp_humi(void);
 
void initTask(osTimerId SpeedTimerHandle);

void init(void);

void reset(void);

#endif
