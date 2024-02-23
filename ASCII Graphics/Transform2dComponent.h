#pragma once
#include "HECS.h"
#include "GBase.h"

namespace hecs {

	struct Transform2dComponent {
		Entity owner;
		Coord local;
		Coord world;
		int parent;
		int first_child;
		int next_sibling;
		int prev_sibling;
		/*Transform2dComponent(Entity oo, Coord ll, Coord ww, int pp, int fc, int ns, int ps)
			: owner{ oo }, local{ ll }, world{ ww }, parent{ pp }, first_child{ fc }, next_sibling{ ns }, prev_sibling{ ps } {
		}*/
	};

	class Transform2dComponentManager {
	public:
		Transform2dComponent* get_component(Entity e);
		const Vector<Transform2dComponent>& components();
		bool has_component(Entity e);
		Transform2dComponent* add_component(Entity owner);
		Transform2dComponent* add_component(Entity owner, short local_x, short local_y);
		Transform2dComponent* add_component(Entity owner, Entity parent);
		Transform2dComponent* add_component(Entity owner, Entity parent, short local_x, short local_y);
		void remove_component(Entity e);
		void move(Entity e, Coord change);
	private:
		Vector<Transform2dComponent> m_components;
		Map<Entity, int> m_map;
		void remove_component(int index);
		void update_world_pos(int index, Coord change);
	};
}