#pragma once
#include "GBase.h"

class Sprite {
public:
	int width() { return m_width; }
	int height() { return m_height; }
	Sprite(int w, int h);

	PixelData pixel_data;
private:
	int m_width;
	int m_height;
};