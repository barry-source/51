#ifndef _TIMER_H_
#define _TIMER_H_

#define Phase 80

extern int leftSpeed;
extern int rightSpeed;

void timer0Init();
void timer1Init();

void timer1InitWithoutInterrupt();
#endif