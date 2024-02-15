#pragma once
#include <vector>
#include "GBase.h"
#include <string>

using PixelData = std::vector<std::vector<Color>>;


class Sprite {
public:
	int width() { return m_width; }
	int height() { return m_height; }
	Sprite(int w, int h);

	void draw(Sprite f, Coord start_point);

	PixelData pixel_data;
private:
	int m_width;
	int m_height;
};