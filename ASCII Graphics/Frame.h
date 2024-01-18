#pragma once
#include <vector>

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

//struct Pixel {
//	char character;
//	Color fcolor;
//	Color bcolor;
//	Pixel() {
//		character = ' ';
//		fcolor = Color{ 255, 255, 255 };
//		bcolor = Color{ 0, 0, 0 };
//	}
//	Pixel(char ch) {
//		character = ch;
//		fcolor = Color{ 255, 255, 255 };
//		bcolor = Color{ 0, 0, 0 };
//	}
//};

using FrameData = std::vector<std::vector<Color>>;


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

	void draw(Frame f, Coord start_point);
	void draw(Shape s);
	void clear();

	//FrameData frame_data() { return m_frame_data; }
	FrameData frame_data;

private:
	int m_width;
	int m_height;
	//FrameData m_frame_data;
};








