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
		frame_data.push_back(std::vector<Color>{});
		for (int x = 0; x < m_width; ++x) {
			//std::cout << "Creating point (" << x << "," << y << ")\n";
			frame_data[y].push_back(Color{0,0,0});
		}
	}
}

void Frame::draw(Frame f, Coord start) {
	Coord end{ start.x + f.width(), start.y + f.height() };
	for (int row = 0; row < f.height(); ++row) {
		for (int col = 0; col < f.width(); ++col) {
			this->frame_data[start.y+col][start.x+row] = f.frame_data[col][row];
		}
	}
}

void Frame::clear() {
	for (int y = 0; y < m_height; ++y) {
		for (int x = 0; x < m_width; ++x) {
			frame_data[y][x] = Color{0,0,0};
		}
	}
}

void Scene::add(Frame entity, Coord position) {
	EntityPosition ep{entity,position};
	/*ep.entity = &entity;
	ep.position = position;*/
	contents.push_back(ep);
}
