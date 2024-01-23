#pragma once
#include "Scene.h"
#include <vector>
#include <iostream>
#include "ConhostController.h"
using CC = ConhostController;

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

FrameCode create_frame_code(Frame frame) {
	FrameData fd = frame.frame_data;
	int frame_height = fd.size();
	int frame_width = fd[0].size();
	Color prev_color{ 0,0,0 };
	std::string row_code = "";
	FrameCode frame_code{};
	for (short row = 0; row < frame_height; ++row) {
		row_code = "";
		for (short col = 0; col < frame_width; ++col) {
			Color current_color = fd[row][col];
			if (current_color != prev_color || row == 0 && col == 0) {
				row_code += to_ansi_fcolor(current_color);
				prev_color = current_color;
			}
			// block char: 219
			row_code += (char)219;
		}
		frame_code.push_back(row_code);
	}
	return frame_code;
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

void Scene::draw() {
	for (int i = 0; i < contents.size(); ++i) {
		EntityPosition& ep = contents[i];
		CC::move_cursor_to(ep.position);
		CC::write(create_frame_code(ep.entity));
	}
}

void Scene::move(int index, Coord new_pos) {
	EntityPosition* ep = &contents[index];
	short width = ep->entity.width();
	short height = ep->entity.height();

	CC::move_cursor_to(new_pos);
	CC::write(create_frame_code(ep->entity));

	Coord old_pos = ep->position;
	Coord change = Coord{ new_pos.x - old_pos.x, new_pos.y - old_pos.y };

	Coord start_pos;
	Coord end_pos;
	FrameCode fc;

	Coord spw;
	Coord epw;
	Coord spt;
	Coord ept;

	// DOWN
	if (change.y > 0) {
		// wide rect
		spw = Coord{ old_pos.x, old_pos.y };
		epw = Coord{ old_pos.x + width, new_pos.y };
		
		// tall rect
		spt.y = new_pos.y;
		ept.y = old_pos.y + height;
		if (change.x > 0) {
			spt.x = old_pos.x;
			ept.x = new_pos.x;
		}
		else if (change.x < 0) {
			spt.x = new_pos.x + width;
			ept.x = old_pos.x + width;
		}
	}

	// UP
	else if (change.y < 0) {
		// wide rect
		spw = Coord{ old_pos.x, new_pos.y + height };
		epw = Coord{ old_pos.x + width, old_pos.y + height };
		
		// tall rect
		spt.y = old_pos.y;
		ept.y = old_pos.y + height;
		if (change.x > 0) {
			spt.x = old_pos.x;
			ept.x = new_pos.x;
		}
		else if (change.x < 0) {
			spt.x = new_pos.x + width;
			ept.x = old_pos.x + width;
		}
	}
	
	// NONE
	else if (change.y == 0) {
		// tall rect
		for (int row = old_pos.y; row < old_pos.y + height; ++row) {
			if (change.x > 0) {
				for (int col = old_pos.x; col < new_pos.x; ++col) {
					CC::move_cursor_to(col, row);
					if (index == 0) CC::set_fcolor(0, 0, 0); // default??
					else CC::set_fcolor(contents[0].entity.frame_data[row][col]);
					CC::write((char)219);
				}
			}
			else if (change.x < 0) {
				for (int col = new_pos.x + width; col < old_pos.x + width; ++col) {
					CC::move_cursor_to(col, row);
					if (index == 0) CC::set_fcolor(0, 0, 0); // default??
					else CC::set_fcolor(contents[0].entity.frame_data[row][col]);
					CC::write((char)219);
				}
			}
		}
	}




	fc = FrameCode{};
	for (int row = start_pos.y; row < end_pos.y; ++row) {
		std::string line = "";
		for (int col = start_pos.x; col < end_pos.x; ++col) {
			if (index == 0) line += to_ansi_fcolor(0, 0, 0); // default??
			else line += to_ansi_fcolor((contents[0].entity.frame_data[row][col]));
			//else line += to_ansi_fcolor(Color{ 0,0,0 });
			line += (char)219;
		}
		fc.push_back(line);
	}
	CC::move_cursor_to(start_pos);
	CC::write(fc);




	ep->position = new_pos;
}
