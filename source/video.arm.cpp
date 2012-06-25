#include "b0rk.h"

void initVideo(void)
{
	FeOS_DirectMode();

	// Disable autoupdates
	FeOS_SetAutoUpdate(AUTOUPD_KEYS, false);
	FeOS_SetAutoUpdate(AUTOUPD_OAM,  false);
	FeOS_SetAutoUpdate(AUTOUPD_BG,   false);
}

void deinitVideo(void)
{
	FeOS_ConsoleMode();
}
