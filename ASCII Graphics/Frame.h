#pragma once

#include <vector>

struct Color {
	int r, g, b;
};

struct Pixel {
	char character;
	Color foreground;
	Color background;
	Pixel() {
		character = ' ';
		foreground = Color{ 255, 255, 255 };
		background = Color{ 0, 0, 0 };
	}
	Pixel(char ch) {
		character = ch;
		foreground = Color{ 255, 255, 255 };
		background = Color{ 0, 0, 0 };
	}
};

typedef std::vector<std::vector<Pixel>> FrameData;

class Shape {
public:
	virtual void draw(FrameData* frame_data);

private:
};

class Frame {
public:
	int width() { return m_width; }
	int height() { return m_height; }
	Frame(int w, int h);
	void draw(Shape s);
	void clear();

	// inefficient?
	void draw(short x, short y, Pixel px);
	FrameData frame_data() { return m_frame_data; }

private:
	int m_width;
	int m_height;
	FrameData m_frame_data;
};









