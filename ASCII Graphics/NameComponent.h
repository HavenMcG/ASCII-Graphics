#pragma once
#include "HECS.h"
#include <string>
#include <vector>
#include <map>

namespace hecs {

	class NameComponentManager {
	public:
		Entity find(String);
		String get_name(Entity e); // returns the first-located name of entity
		Vector<String> get_all_names(Entity e); // returns all names of entity
		bool add_component(Entity e, String name);

	private:
		Map<String, Entity> m_components;
	};
}