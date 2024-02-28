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
		return Rect{ Coord{ r.Left,r.Top },Coord{ r.Right,r.Bottom } };
	}
	static SMALL_RECT to_winsmallrect(Rect r) {
		return SMALL_RECT{ r.top_left.x, r.top_left.y, r.bottom_right.x, r.bottom_right.y };
	}
}