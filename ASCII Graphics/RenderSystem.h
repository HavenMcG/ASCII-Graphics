#pragma once
#include "SpriteComponent.h"
#include "Transform2dComponent.h"
//#include "Renderer.h"
#include "ConhostController.h"

namespace hecs {

	class ConsoleRenderer {
	public:
		ConsoleRenderer(ConhostController* cccc) : cc{ cccc } {}
		void render(SpriteComponentManager* sprites, Transform2dComponentManager* transforms);
		void draw(PixelData sp, Coord position);
		//void move(int index, Coord new_pos);
	private:
		ConhostController* cc;
		using RenderCode = Vector<String>;
		RenderCode create_render_code(PixelData pd);
		void write(RenderCode rc);
		PixelData last_frame = PixelData{};
	};
}