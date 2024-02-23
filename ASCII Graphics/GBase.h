#pragma once
#include <vector>
#include <string>
#include <map>

struct Coord {
	short x;
	short y;
	Coord() {
		x = 0;
		y = 0;
	}
	Coord(short xx, short yy) : x{ xx }, y{ yy } {}
	Coord(int xx, int yy) : x{ static_cast<short>(xx) }, y{ static_cast<short>(yy) } {}
	Coord(short xx, int yy) : x{ xx }, y{ static_cast<short>(yy) } {}
	Coord(int xx, short yy) : x{ static_cast<short>(xx) }, y{ yy } {}
};
Coord operator+(Coord lhs, Coord rhs);
bool operator==(Coord lhs, Coord rhs);
bool operator!=(Coord lhs, Coord rhs);

struct Color {
	int r, g, b;
	Color() : r{ 0 }, g{ 0 }, b{ 0 } {}
	Color(int rn, int gn, int bn) : r{ rn }, g{ gn }, b{ bn } {}
};
bool operator==(const Color lhs, const Color rhs);
bool operator!=(const Color lhs, const Color rhs);

//using PixelData = std::vector<std::vector<Color>>;
struct PixelData {
	short width;
	short height;
	std::vector<Color> data;
	PixelData() : width{ 0 }, height{ 0 }, data{ std::vector<Color>{} } {}
	PixelData(short ww, short hh) : width{ ww }, height{ hh } {
		data = std::vector<Color>(ww * hh);
	}
	Color& pixel(short x, short y);
	Color& pixel(Coord coord);
};