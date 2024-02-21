#pragma once
#include "HECS.h"
#include "GBase.h"

namespace hecs {

	struct SpriteComponent {
		PixelData pixel_data;
	};

	class SpriteComponentManager {
	public:
		SpriteComponent get_component(Entity e);
	};
}