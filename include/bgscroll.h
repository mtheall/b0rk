#pragma once

#ifdef FEOS
#include <feos.h>
#else
#include <nds.h>
#endif

class BGScroller {
private:
	const u16 *bgMap;
	u16 *workMap;
	s32 scrollX;
	s32 scrollY;
	s32 width;
	s32 height;
	bool updated;
	void copyRow(s32 tx, s32 ty, u8 length = 33);
public:
	BGScroller(const u16 *map,            // source map
	           u16 *workmap,              // pre-allocated workmap u16[512*256]
	           s32 x, s32 y,              // starting position measured in pixels
	           s32 width, s32 height);    // dimensions of source map measured in 8x8 tiles

	void scroll(s32 x, s32 y);            // scroll to this position measured in pixels

	bool wasUpdated() { return updated; } // if the map was modified in the last scroll()
	s32  getX()       { return scrollX; } // get the x position
	s32  getY()       { return scrollY; } // get the y position
};
