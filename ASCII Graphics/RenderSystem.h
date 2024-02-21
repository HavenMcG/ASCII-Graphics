#pragma once
#include "SpriteComponent.h"
#include "Transform2dComponent.h"
#include "Renderer.h"

namespace hecs {
	class RenderSystem {
	public:
		void render(ConArt::ConsoleRenderer r, SpriteComponentManager sprites, Transform2dComponentManager transforms);

	};
}