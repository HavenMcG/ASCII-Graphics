#pragma once
#include "GBase.h"
#include "Sprite.h"

namespace ConArt {

	class Renderer {
	public:
		virtual void draw(Sprite) = 0;
	};

	class ConsoleRenderer : Renderer {
	public:
		void draw(Sprite sp);
	private:
		using RenderCode = std::vector<std::string>;
		RenderCode create_render_code(Sprite sprite);

		// these probably shouldn't be here
		std::string to_ansi_fcolor(Color c);
		std::string to_ansi_fcolor(int r, int g, int b);
		std::string to_ansi_bcolor(Color c);
		std::string to_ansi_bcolor(int r, int g, int b);
	};
}