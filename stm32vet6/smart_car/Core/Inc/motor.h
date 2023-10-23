#include <stdint.h>

#ifndef _MOTOR_H_
#define _MOTOR_H_

#define NORMAL 0
#define PWM 1

void changeMode(uint8_t m);

void forward(void);

void backward(void);

void leftward(void);

void rightward(void);

void hor_leftward(void);

void hor_rightward(void);

void stop(void);

#endif
