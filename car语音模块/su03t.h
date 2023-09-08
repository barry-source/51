#ifndef _SU03T_H_
#define _SU03T_H_

enum Mode {
	tracingMode,
	avoidMode,
	followMode,
	stopMode
};

extern enum Mode mode;

enum Mode getMode();

#endif