#pragma once

#include "GBase.h"

namespace hecs {

	using Entity = unsigned;

	struct Transform2dComponent {
		short x;
		short y;
	};

	struct SpriteComponent {
		PixelData pxd;
	};

	class EntityManager {
	public:
		int create_entity();

	private:
		std::vector<Entity> m_entities;
		Entity m_next_entity = 0;
	};

	class NameComponentManager {
	public:
		Entity find(std::string);
		std::string get_name(Entity e); // returns the first-located name of entity
		std::vector<std::string> get_all_names(Entity e); // returns all names of entity
		bool add_component(Entity e, std::string name);

	private:
		std::map<std::string, Entity> m_components;
	};
}