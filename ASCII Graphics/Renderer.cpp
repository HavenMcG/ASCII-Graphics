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

std::string ConsoleRenderer::to_ansi_fcolor(Color c) {
	return "\033[38;2;" + std::to_string(c.r) + ";" + std::to_string(c.g) + ";" + std::to_string(c.b) + "m";
}

std::string ConsoleRenderer::to_ansi_fcolor(int r, int g, int b) {
	return to_ansi_fcolor(Color{ r,g,b });
}

std::string ConsoleRenderer::to_ansi_bcolor(Color c) {
	return "\033[48;2;" + std::to_string(c.r) + ";" + std::to_string(c.g) + ";" + std::to_string(c.b) + "m";
}

std::string ConsoleRenderer::to_ansi_bcolor(int r, int g, int b) {
	return to_ansi_bcolor(Color{ r,g,b });
}
