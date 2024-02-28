#pragma once
#include "SpriteComponent.h"
#include "Transform2dComponent.h"
#include "Window.h"
#include "ANSI.h"

namespace hecs {
	using RenderCode = std::vector<std::string>;

	class ConsoleRenderer {
	public:
		ConsoleRenderer(hcon::Window* wwww, hcon::Buffer* bb1, hcon::Buffer* bb2)
			: ww{ wwww }, b1{ bb1 }, b2{ bb2 }, tb{ b1 }, last_frame{ &b1_last_frame } {}
		void render(SpriteComponentManager* sprites, Transform2dComponentManager* transforms);
		void draw(PixelData sp, Coord position);
		//void move(int index, Coord new_pos);
	private:
		hcon::Window* ww;
		hcon::Buffer* b1;
		hcon::Buffer* b2;
		hcon::Buffer* tb;
		using RenderCode = Vector<String>;
		RenderCode create_render_code(PixelData pd);
		void write(RenderCode rc);
		PixelData b1_last_frame;
		PixelData b2_last_frame;
		PixelData* last_frame;
	};
}