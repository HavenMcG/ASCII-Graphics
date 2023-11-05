#pragma once
#include "Frame.h"
#include <vector>
#include <iostream>

class Frame {
private:
	int m_width;
	int m_height;
	std::vector<std::vector<char>> m_frame_data;

public:
	int width() { return m_width; }
	int height() { return m_height; }

	Frame(int w, int h)
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

	void display() {
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

	void draw(Line l) {
		for (int y = 0; y < m_height; ++y) {
			for (int x = 0; x < m_width; ++x) {
				//std::cout << "Checking point (" << x << "," << y << ")\n";
				if (l.has_point(x, y)) m_frame_data[y][x] = (char)219;
			}
		}
	}

	void clear() {
		for (int y = 0; y < m_height; ++y) {
			for (int x = 0; x < m_width; ++x) {
				m_frame_data[y][x] = ' ';
			}
		}
	}
};