#pragma once
#include "GBase.h"
#include "Sprite.h"
#include "Scene.h"
#include "ConhostController.h"

namespace ConArt {

	class Renderer {
	public:
		virtual void draw(Sprite*) = 0;
	};

	class ConsoleRenderer : Renderer {
	public:
		ConsoleRenderer(ConhostController* cccc) : cc{ cccc } {}
		void draw(Sprite* sp);
		void draw(Scene* sc);
		void move(Scene* sc, int index, Coord new_pos);
	private:
		ConhostController* cc;
		using RenderCode = std::vector<std::string>;
		RenderCode create_render_code(Sprite sprite);
		void write(RenderCode rc);
	};
}