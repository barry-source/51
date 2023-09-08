#include "reg52.h"
#include "carFunction.h"
#include "su03t.h"

sbit led = P3^6;

void main() {
	init();
	while(1) {
		switch (getMode()) {
			case tracingMode:
				traceing();
				break;
			case followMode:
				follow();
				break;
			case avoidMode:
				avoid();
				break;
			case stopMode:
				break;
		}
	}
}



