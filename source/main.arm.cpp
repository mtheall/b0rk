#include <feos.h>

int main(int argc, char *argv[]) {
	FeOS_DirectMode();

	// Disable key autoupdate because it may cause
	// side effects if the processing takes too long
	FeOS_SetAutoUpdate(AUTOUPD_KEYS, false);

	for (;;)
	{
		swiWaitForVBlank();
		scanKeys();
		if (keysDown() & KEY_START)
			break;
	}

	FeOS_ConsoleMode();
	return 0;
}
