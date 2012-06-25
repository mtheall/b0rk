#include <feos.h>

int main(int argc, char *argv[]) {
	FeOS_DirectMode();

	// Disable autoupdates because I want to
	// do them myself
	FeOS_SetAutoUpdate(AUTOUPD_KEYS, false);
	FeOS_SetAutoUpdate(AUTOUPD_KEYS, false);
	FeOS_SetAutoUpdate(AUTOUPD_BG,   false);

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
