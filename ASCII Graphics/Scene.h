#pragma once
#include <vector>
#include "GBase.h"
#include <string>

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
using FrameCode = std::vector<std::string>;

class Frame {
public:
	int width() { return m_width; }
	int height() { return m_height; }
	Frame(int w, int h);

	void draw(Frame f, Coord start_point);
	void clear();

	//FrameData frame_data() { return m_frame_data; }
	FrameData frame_data;
private:
	int m_width;
	int m_height;
	//FrameData m_frame_data;
};
FrameCode create_frame_code(Frame frame);

struct EntityPosition {
	Frame entity;
	Coord position;
};

struct Scene {
	std::vector<EntityPosition> contents;
	void add(Frame entity, Coord position);
	void draw();
	void move(int i, Coord new_pos);
};





