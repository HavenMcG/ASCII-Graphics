#pragma once

struct Coord {
	short x;
	short y;
};

struct Color {
	int r, g, b;
	Color() {
		r = 0;
		g = 0;
		b = 0;
	}
	Color(int rn, int gn, int bn) {
		r = rn;
		g = gn;
		b = bn;
	}
};
bool operator==(const Color lhs, const Color rhs);
bool operator!=(const Color lhs, const Color rhs);
