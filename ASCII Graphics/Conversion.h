#pragma once
#include <Windows.h>
#include "GBase.h"

namespace hcon {

	static Coord to_coord(COORD c) {
		return Coord{ c.X, c.Y };
	}
	static COORD to_wincoord(Coord c) {
		return COORD{ c.x, c.y };
	}
	static Rect to_rect(SMALL_RECT r) {
		return Rect{ r.Left, r.Top, r.Right, r.Bottom };
	}
	static SMALL_RECT to_winsmallrect(Rect r) {
		return SMALL_RECT{ r.left, r.top, r.right, r.bottom };
	}
}