#include "b0rk.h"

int main(int argc, char *argv[]) {
	initVideo();

	for (;;)
	{
		swiWaitForVBlank();
		scanKeys();
		if (keysDown() & KEY_START)
			break;
	}

	deinitVideo();
	return 0;
}
