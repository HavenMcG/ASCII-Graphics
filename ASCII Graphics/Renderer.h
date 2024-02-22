#pragma once
#include "GBase.h"
#include "ConhostController.h"

namespace ConArt {

	class Renderer {
	};

	class ConsoleRenderer : Renderer {
	public:
		ConsoleRenderer(ConhostController* cccc) : cc{ cccc } {}
		void draw(PixelData sp, Coord position);
		//void move(int index, Coord new_pos);
	private:
		ConhostController* cc;
		using RenderCode = std::vector<std::string>;
		RenderCode create_render_code(PixelData pd);
		void write(RenderCode rc);
	};
}