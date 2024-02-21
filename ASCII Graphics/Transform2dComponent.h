#pragma once
#include "HECS.h"

namespace hecs {

	struct Transform2dComponent {
		short x;
		short y;
	};

	class Transform2dComponentManager {
	public:
		Transform2dComponent* get_component(Entity e);
		bool has_component(Entity e);
		void add_component(Entity e);
		void remove_component(Entity e);
	private:
		Vector<Transform2dComponent> m_components;
		Map<Entity, int> m_map;
	};
}