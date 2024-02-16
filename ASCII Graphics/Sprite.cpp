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