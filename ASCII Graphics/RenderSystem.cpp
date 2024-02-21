#include "RenderSystem.h"

namespace hecs {
	void RenderSystem::render(ConArt::ConsoleRenderer r, SpriteComponentManager sprite_manager, Transform2dComponentManager transform_manager) {
		
		auto& sprites = sprite_manager.components();

		Entity e;
		SpriteComponent sp;
		Transform2dComponent* pos;
		for (int i = 0; i < sprites.size(); ++i) {
			e = sprites[i].owner;
			sp = sprites[i];
			pos = transform_manager.get_component(e);
			r.draw(sp.pixel_data, Coord{ pos->x,pos->y });
		}
	}
}