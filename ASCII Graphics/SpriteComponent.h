#pragma once
#include "HECS.h"
#include "GBase.h"

namespace hecs {

	struct SpriteComponent {
		Entity owner;
		PixelData pixel_data;
	};

	struct SpriteComponentManager {
	public:
		SpriteComponent* get_component(Entity e);
		const Vector<SpriteComponent>& components();
		bool has_component(Entity e);
		void add_component(Entity e);
		void remove_component(Entity e);
	private:
		Vector<SpriteComponent> m_components;
		Map<Entity, int> m_map;
	};
}