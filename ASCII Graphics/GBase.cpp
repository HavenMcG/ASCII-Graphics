#include "GBase.h"

Coord operator+(Coord lhs, Coord rhs) {
	return Coord{ lhs.x + rhs.x, lhs.y + rhs.y };
}

bool operator==(Coord lhs, Coord rhs) {
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator!=(Coord lhs, Coord rhs) {
	return !(lhs == rhs);
}

bool operator==(const Color lhs, const Color rhs) {
	return (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b);
}
bool operator!=(const Color lhs, const Color rhs) {
	return !(lhs == rhs);
}

Color& PixelData::pixel(short x, short y) {
	return data[x + (y * width)];
}

Color& PixelData::pixel(Coord coord) {

	return data[coord.x + (coord.y * width)];
}
