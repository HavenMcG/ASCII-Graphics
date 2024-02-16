#include "Renderer.h"
#include "ConhostController.h"
using namespace ConArt;

ConsoleRenderer::RenderCode ConsoleRenderer::create_render_code(Sprite sprite) {
	PixelData pd = sprite.pixel_data;
	int frame_height = pd.size();
	int frame_width = pd[0].size();
	Color prev_color{ 0,0,0 };
	std::string row_code = "";
	RenderCode frame_code{};
	for (short row = 0; row < frame_height; ++row) {
		row_code = "";
		for (short col = 0; col < frame_width; ++col) {
			Color current_color = pd[row][col];
			if (current_color != prev_color || row == 0 && col == 0) {
				row_code += to_ansi_bcolor(current_color);
				prev_color = current_color;
			}
			// block char: 219
			row_code += ' ';
		}
		frame_code.push_back(row_code);
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

void ConArt::ConsoleRenderer::draw(Sprite* sp) {
	write(create_render_code(*sp));
}

void ConsoleRenderer::draw(Scene* sc) {
	for (int i = 0; i < sc->contents.size(); ++i) {
		SpritePosition& ep = sc->contents[i];
		cc->move_cursor_to(ep.position);
		write(create_render_code(ep.sprite));
	}
}

void ConsoleRenderer::move(Scene* sc, int index, Coord new_pos) {
	SpritePosition* ep = &sc->contents[index];
	short width = ep->sprite.width();
	short height = ep->sprite.height();

	// draw the entity in it's new position:
	cc->move_cursor_to(new_pos);
	write(create_render_code(ep->sprite));

	// figure out what we need to erase:
	Coord old_pos = ep->position;
	Coord change = Coord{ new_pos.x - old_pos.x, new_pos.y - old_pos.y };

	Coord start_w{ 0,0 }; // wide rectangle
	Coord end_w{ 0,0 };
	Coord start_t{ 0,0 }; // tall rectangle
	Coord end_t{ 0,0 };

	if (change.x >= width || change.y >= height) { // no overlap between old and new positions.
		start_w = old_pos;
		end_w = Coord{ old_pos.x + width, old_pos.y + height };
	}
	else { // there is overlap, we erase only what we didn't already overwrite.
		if (change.y > 0) {
			start_w = Coord{ old_pos.x, old_pos.y };
			end_w = Coord{ old_pos.x + width, new_pos.y };
			start_t.y = new_pos.y;
			end_t.y = old_pos.y + height;
		}
		else if (change.y < 0) {
			start_w = Coord{ old_pos.x, new_pos.y + height };
			end_w = Coord{ old_pos.x + width, old_pos.y + height };
			start_t.y = old_pos.y;
			end_t.y = old_pos.y + height;
		}
		else if (change.y == 0) {
			start_t.y = old_pos.y;
			end_t.y = old_pos.y + height;
		}
		if (change.x > 0) {
			start_t.x = old_pos.x;
			end_t.x = new_pos.x;
		}
		else if (change.x < 0) {
			start_t.x = new_pos.x + width;
			end_t.x = old_pos.x + width;
		}
	}

	// wide rect
	if (end_w.x - start_w.x > 0) {
		RenderCode wide;
		Color prev_color;
		for (int row = start_w.y; row < end_w.y; ++row) {
			std::string row_code = "";
			for (int col = start_w.x; col < end_w.x; ++col) {
				Color current_color{ 0,0,0 }; // default??
				if (index != 0) current_color = (sc->contents[0].sprite.pixel_data[row][col]);
				if (current_color != prev_color || row == 0 && col == 0) {
					row_code += to_ansi_bcolor(current_color);
					prev_color = current_color;
				}
				// 219 = block character
				row_code += ' ';
			}
			wide.push_back(row_code);
		}
		cc->move_cursor_to(start_w);
		write(wide);
	}

	// tall rect
	if (end_t.x - start_t.x > 0) {
		RenderCode tall;
		Color prev_color;
		for (int row = start_t.y; row < end_t.y; ++row) {
			std::string row_code = "";
			for (int col = start_t.x; col < end_t.x; ++col) {
				Color current_color{ 0,0,0 }; // default??
				if (index != 0) current_color = (sc->contents[0].sprite.pixel_data[row][col]);
				if (current_color != prev_color || row == 0 && col == 0) {
					row_code += to_ansi_bcolor(current_color);
					prev_color = current_color;
				}
				// 219 = block character
				row_code += ' ';
			}
			tall.push_back(row_code);
		}
		cc->move_cursor_to(start_t);
		write(tall);
	}

	ep->position = new_pos;
}