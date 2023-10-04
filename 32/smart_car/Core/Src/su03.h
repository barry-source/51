#ifndef _SU03_H_
#define _SU03_H_

enum Mode {
	stopMode = 0,
	tracingMode,
	avoidMode,
	followMode,
	gestureMode,
	testMode,
};

extern enum Mode runMode;

enum Mode get_mode(void);

#endif
