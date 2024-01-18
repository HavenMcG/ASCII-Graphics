#pragma once
#include "Frame.h"
#include <vector>
#include <iostream>

bool operator==(const Color lhs, const Color rhs) {
	return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}
bool operator!=(const Color lhs, const Color rhs) {
	return !(lhs == rhs);
}

Frame::Frame(int w, int h)
	: m_width{ w }
	, m_height{ h } {
	for (int y = 0; y < h; ++y) {
		m_frame_data.push_back(std::vector<Color>{});
		for (int x = 0; x < m_width; ++x) {
			//std::cout << "Creating point (" << x << "," << y << ")\n";
			m_frame_data[y].push_back(Color{0,0,0});
		}
	}
}

void Frame::draw(Shape s) {
	//for (int y = 0; y < m_height; ++y) {
	//	for (int x = 0; x < m_width; ++x) {
	//		//std::cout << "Checking point (" << x << "," << y << ")\n";
	//		if (s.has_point(x, y)) m_frame_data[y][x] = (char)219;
	//	}
	//}
	// 
	//s.draw(&m_frame_data);
}

void Frame::clear() {
	for (int y = 0; y < m_height; ++y) {
		for (int x = 0; x < m_width; ++x) {
			m_frame_data[y][x] = Color{0,0,0};
		}
	}
}
