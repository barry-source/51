#include "su03.h"

// Ĭ��stopMode
enum Mode runMode = stopMode;

enum Mode get_mode() {
	return runMode;
}
