#include "motor.h"
#include "reg52.h"

sbit rightA1 = P3^2; // 向后
sbit rightA2 = P3^3; // 向前
sbit leftB1 = P3^4;  // 向后
sbit leftB2 = P3^5;  // 向前

void forward() {
	rightA1 = 0;
	rightA2 = 1;
	leftB1 = 0;
	leftB2 = 1;
}

void backward() {
	rightA1 = 1;
	rightA2 = 0;
	leftB1 = 1;
	leftB2 = 0;
}

// 前左
void leftward() {
	rightA1 = 0;
	rightA2 = 1;
	leftB1 = 0;
	leftB2 = 0;
}

// 前右
void rightward() {
	rightA1 = 0;
	rightA2 = 0;
	leftB1 = 0;
	leftB2 = 1;
}

void stop() {
	rightA1 = 0;
	rightA2 = 0;
	leftB1 = 0;
	leftB2 = 0;
}

void leftForward() {
	leftB1 = 0;
	leftB2 = 1;
}

void leftStop() {
	leftB1 = 0;
	leftB2 = 0;
}

void rightForward() {
	rightA1 = 0;
	rightA2 = 1;
}

void rightStop() {
	rightA1 = 0;
	rightA2 = 0;
}