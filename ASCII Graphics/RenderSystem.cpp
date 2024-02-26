#include "RenderSystem.h"

//temp
#include <iostream>
using std::cout;

namespace hecs {
	void ConsoleRenderer::render(SpriteComponentManager* sprite_manager, Transform2dComponentManager* transform_manager) {

		PixelData frame{ cc->canvas_width(), cc->canvas_height() };

		for (int i = 0; i < sprite_manager->m_components.size(); ++i) {

			Entity e = sprite_manager->m_components[i].owner;
			Coord& pos = transform_manager->get_component(e)->world;
			PixelData& pd = sprite_manager->m_components[i].pixel_data;

			for (int row = 0; row < pd.height; ++row) {
				for (int col = 0; col < pd.width; ++col) {
					frame.pixel(pos.x+col,pos.y+row) = pd.pixel(col, row);
				}
			}

		}
		
		//if (frame.width == last_frame.width && frame.height == last_frame.height) {
		//	RenderCode rc = RenderCode{};
		//	String row_code = "";
		//	Coord start; // beginning of changed area
		//	bool writing = false;
		//	Color current;
		//	Color previous;
		//	//cc->move_cursor_to(0, 0);
		//	for (int row = 0; row < frame.height; ++row) {
		//		for (int col = 0; col < frame.width; ++col) {
		//			current = frame.pixel(col, row);
		//			previous = last_frame.pixel(col, row);
		//			if (current != previous) {
		//				if (writing) {
		//					row_code += to_ansi_bcolor(current);
		//					row_code += ' ';
		//				}
		//				else {
		//					writing = true;
		//					start = { col,row };
		//					row_code += to_ansi_bcolor(current);
		//					row_code += ' ';
		//				}
		//			}
		//			else {
		//				if (writing) {
		//					writing = false;
		//					rc.push_back(row_code);
		//					cc->move_cursor_to(start);
		//					write(rc);
		//					rc = RenderCode{};
		//					row_code = "";
		//				}
		//			}
		//		}
		//		if (writing) {
		//			writing = false;
		//			rc.push_back(row_code);
		//			cc->move_cursor_to(start);
		//			write(rc);
		//			rc = RenderCode{};
		//			row_code = "";
		//		}
		//	}
		//}
		//else {
		//	draw(frame, Coord{ 0,0 });
		//}

		//std::swap(frame, last_frame);

		cc->switch_target_buffer();
		cc->move_cursor_to(0, 0);
		draw(frame, Coord{ 0,0 });
		cc->switch_display_buffer();

		/*for (int i = 0; i < sprite_manager->m_components.size(); ++i) {
			e = sprite_manager->m_components[i].owner;
			pos = transform_manager->get_component(e);
			draw(sprite_manager->m_components[i].pixel_data, pos->world);
		}*/
	}

	RenderCode ConsoleRenderer::create_render_code(PixelData pd) {
		Color prev_color{ 0,0,0 };
		std::string row_code = "";
		RenderCode frame_code{};
		for (int i = 0; i < pd.data.size(); ++i) {
			Color current_color = pd.data[i];
			if (current_color != prev_color || i == 0) {
				row_code += to_ansi_bcolor(current_color);
				prev_color = current_color;
			}
			row_code += ' ';
			if ((i + 1) % pd.width == 0) {
				frame_code.push_back(row_code);
				row_code = "";
			}
		}
		return frame_code;
	}

	void ConsoleRenderer::write(RenderCode rc) {
		Coord start_pos = cc->cursor_position();
		for (int i = 0; i < rc.size(); ++i) {
			cc->move_cursor_to(start_pos.x, start_pos.y + i);
			cc->write(rc[i]);
		}
	}

	void ConsoleRenderer::draw(PixelData pd, Coord position) {
		cc->move_cursor_to(position);
		write(create_render_code(pd));
	}

}

//void ConsoleRenderer::move(int index, Coord new_pos) {
//	SpritePosition* ep = &sc->contents[index];
//	short width = ep->sprite.width();
//	short height = ep->sprite.height();
//
//	// draw the entity in it's new position:
//	cc->move_cursor_to(new_pos);
//	write(create_render_code(ep->sprite));
//
//	// figure out what we need to erase:
//	Coord old_pos = ep->position;
//	Coord change = Coord{ new_pos.x - old_pos.x, new_pos.y - old_pos.y };
//
//	Coord start_w{ 0,0 }; // wide rectangle
//	Coord end_w{ 0,0 };
//	Coord start_t{ 0,0 }; // tall rectangle
//	Coord end_t{ 0,0 };
//
//	if (change.x >= width || change.y >= height) { // no overlap between old and new positions.
//		start_w = old_pos;
//		end_w = Coord{ old_pos.x + width, old_pos.y + height };
//	}
//	else { // there is overlap, we erase only what we didn't already overwrite.
//		if (change.y > 0) {
//			start_w = Coord{ old_pos.x, old_pos.y };
//			end_w = Coord{ old_pos.x + width, new_pos.y };
//			start_t.y = new_pos.y;
//			end_t.y = old_pos.y + height;
//		}
//		else if (change.y < 0) {
//			start_w = Coord{ old_pos.x, new_pos.y + height };
//			end_w = Coord{ old_pos.x + width, old_pos.y + height };
//			start_t.y = old_pos.y;
//			end_t.y = old_pos.y + height;
//		}
//		else if (change.y == 0) {
//			start_t.y = old_pos.y;
//			end_t.y = old_pos.y + height;
//		}
//		if (change.x > 0) {
//			start_t.x = old_pos.x;
//			end_t.x = new_pos.x;
//		}
//		else if (change.x < 0) {
//			start_t.x = new_pos.x + width;
//			end_t.x = old_pos.x + width;
//		}
//	}
//
//	// wide rect
//	if (end_w.x - start_w.x > 0) {
//		RenderCode wide;
//		Color prev_color;
//		for (int row = start_w.y; row < end_w.y; ++row) {
//			std::string row_code = "";
//			for (int col = start_w.x; col < end_w.x; ++col) {
//				Color current_color{ 0,0,0 }; // default??
//				if (index != 0) current_color = (sc->contents[0].sprite.pixel_data[row][col]);
//				if (current_color != prev_color || row == 0 && col == 0) {
//					row_code += to_ansi_bcolor(current_color);
//					prev_color = current_color;
//				}
//				// 219 = block character
//				row_code += ' ';
//			}
//			wide.push_back(row_code);
//		}
//		cc->move_cursor_to(start_w);
//		write(wide);
//	}
//
//	// tall rect
//	if (end_t.x - start_t.x > 0) {
//		RenderCode tall;
//		Color prev_color;
//		for (int row = start_t.y; row < end_t.y; ++row) {
//			std::string row_code = "";
//			for (int col = start_t.x; col < end_t.x; ++col) {
//				Color current_color{ 0,0,0 }; // default??
//				if (index != 0) current_color = (sc->contents[0].sprite.pixel_data[row][col]);
//				if (current_color != prev_color || row == 0 && col == 0) {
//					row_code += to_ansi_bcolor(current_color);
//					prev_color = current_color;
//				}
//				// 219 = block character
//				row_code += ' ';
//			}
//			tall.push_back(row_code);
//		}
//		cc->move_cursor_to(start_t);
//		write(tall);
//	}
//
//	ep->position = new_pos;
//}