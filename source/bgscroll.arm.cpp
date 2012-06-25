#ifdef FEOS
#include <feos.h>
#else
#include <nds.h>
#endif
#include "bgscroll.h"

static inline u32 getXY(s32 x, s32 y) {
	x &= 63; // wrap x around 64
	y &= 31; // wrap y around 32
	return y*32 + (x&31) + (x<32 ? 0 : 1024);
}

BGScroller::BGScroller(const u16 *map, u16 *workmap, s32 x, s32 y, s32 width, s32 height)
	: bgMap(map), workMap(workmap),
	  scrollX(x), scrollY(y),
	  width(width), height(height),
	  updated(true) {

	// initialize the map
	for(int i = 0; i < 25; i++)
		copyRow(0, i);
}

void BGScroller::copyRow(s32 tx, s32 ty, u8 length) {
	tx &= (width-1);
	ty &= (height-1);

	u16 *dst = &workMap[(ty%32) * 32];
	const u16 *src = &bgMap[ty * width];

	for(int i = 0; i < length; i++, ++tx &= (width-1))
		dst[tx%32 + (tx%64 < 32 ? 0 : 1024)] = src[tx];
}

void BGScroller::scroll(s32 x, s32 y) {
	updated = false;

	// get (x, y) tile number
	s32 tx = (x>>3) & (width-1);
	s32 ty = (y>>3) & (height-1);

	// get number of tiles scrolled
	s32 dx = (x>>3) - (scrollX>>3);
	s32 dy = (y>>3) - (scrollY>>3);

	if(dx|dy)
		updated = true;

	if(dy < 0) {
		// copy the new full rows
		if(dy < -25) dy = -25;
		for(int i = 0; i > dy; i--)
			copyRow(tx, ty-i);

		// copy the new partial rows
		if(dx > 0) tx += 33-dx;
		else       dx  = -dx;
		for(int i = dy; i > -25; i--)
			copyRow(tx, ty-i, dx);
	}
	else {
		// copy the new full rows
		if(dy > 25) dy = 25;
		for(int i = 0; i < dy; i++)
			copyRow(tx, ty-i+24);

		// copy the new partial rows
		if(dx > 0) tx += 33-dx;
		else       dx  = -dx;
		for(int i = dy; i < 25; i++)
			copyRow(tx, ty-i+24, dx);
	}

	// update scroll info
	scrollX = x;
	scrollY = y;
}
