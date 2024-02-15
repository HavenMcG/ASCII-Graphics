#include "Sprite.h"

Sprite::Sprite(int w, int h)
	: m_width{ w }
	, m_height{ h } {
	for (int y = 0; y < h; ++y) {
		pixel_data.push_back(std::vector<Color>{});
		for (int x = 0; x < m_width; ++x) {
			//std::cout << "Creating point (" << x << "," << y << ")\n";
			pixel_data[y].push_back(Color{ 0,0,0 });
		}
	}
}

void Sprite::draw(Sprite f, Coord start) {
	Coord end{ start.x + f.width(), start.y + f.height() };
	for (int row = 0; row < f.height(); ++row) {
		for (int col = 0; col < f.width(); ++col) {
			this->pixel_data[start.y + col][start.x + row] = f.pixel_data[col][row];
		}
	}
}

//RenderCode create_render_code(Sprite sprite) {
//	PixelData pd = sprite.pixel_data;
//	int frame_height = pd.size();
//	int frame_width = pd[0].size();
//	Color prev_color{ 0,0,0 };
//	std::string row_code = "";
//	RenderCode frame_code{};
//	for (short row = 0; row < frame_height; ++row) {
//		row_code = "";
//		for (short col = 0; col < frame_width; ++col) {
//			Color current_color = pd[row][col];
//			if (current_color != prev_color || row == 0 && col == 0) {
//				row_code += to_ansi_fcolor(current_color);
//				prev_color = current_color;
//			}
//			// block char: 219
//			row_code += (char)219;
//		}
//		frame_code.push_back(row_code);
//	}
//	return frame_code;
//}