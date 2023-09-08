#include "su03t.h"
#include "reg52.h"

sbit a25 = P1^5;
sbit a26 = P1^6;
sbit a27 = P1^7;

enum Mode mode = stopMode;

enum Mode getMode() {
	if(a25 == 0 && a26 == 1 && a27 == 1) {
		mode = tracingMode;
	}
		
	if(a25 == 1 && a26 == 0 && a27 == 1) {
		mode = followMode;
	}
	
	if(a25 == 1 && a26 == 1 && a27 == 0) {
		mode = avoidMode;
	}
	
	if(a25 == 0 && a26 == 0 && a27 == 0) {
		mode = stopMode;
	}
	return mode;
}

