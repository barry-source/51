#ifndef _SU03_H_
#define _SU03_H_

enum Mode {
	stopMode = 0,
	tracingMode,
	avoidMode,
	followMode,
};

extern enum Mode runMode;

enum Mode getMode(void);

#endif
