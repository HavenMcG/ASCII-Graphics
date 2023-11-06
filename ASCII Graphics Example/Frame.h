#pragma once

#include <vector>

class Shape {
public:
	virtual void draw(std::vector<std::vector<char>>* frame_data);
};

class Frame {
private:
	int m_width;
	int m_height;
	std::vector<std::vector<char>> m_frame_data;

public:
	int width() { return m_width; }
	int height() { return m_height; }

	Frame(int w, int h);

	void display();

	void draw(Shape s);

	void clear();
};