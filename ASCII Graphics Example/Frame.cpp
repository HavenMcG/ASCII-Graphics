#pragma once
#include "Frame.h"
#include <vector>
#include <iostream>

Frame::Frame(int w, int h)
	: m_width{ w }
	, m_height{ h } {
	for (int y = 0; y < h; ++y) {
		m_frame_data.push_back(std::vector<char>{});
		for (int x = 0; x < m_width; ++x) {
			//std::cout << "Creating point (" << x << "," << y << ")\n";
			m_frame_data[y].push_back(' ');
		}
	}
}

void Frame::display() {
	for (int row = 0; row < m_frame_data.size(); ++row) {
		for (int col = 0; col < m_frame_data[row].size(); ++col) {
			std::cout << m_frame_data[row][col];
		}
		std::cout << "\n";
	}
	/*for (std::vector<char> row : screen) {
		for (char c : row) {
			std::cout << c;
		}
		std::cout << 'X';
	}*/
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
			m_frame_data[y][x] = ' ';
		}
	}
}
