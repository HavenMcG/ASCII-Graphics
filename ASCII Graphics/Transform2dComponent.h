#pragma once
#include "HECS.h"

namespace hecs {

	struct Transform2dComponent {
		Entity owner;
		short x;
		short y;
	};

	class Transform2dComponentManager {
	public:
		Transform2dComponent* get_component(Entity e);
		const Vector<Transform2dComponent>& components();
		bool has_component(Entity e);
		Transform2dComponent* add_component(Entity e);
		Transform2dComponent* add_component(Entity e, short x, short y);
		void remove_component(Entity e);
	private:
		Vector<Transform2dComponent> m_components;
		Map<Entity, int> m_map;
	};
}