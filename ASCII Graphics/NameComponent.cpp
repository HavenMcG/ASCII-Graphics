#include "NameComponent.h"

namespace hecs {

	Entity NameComponentManager::find(String name) {
		auto it = m_components.find(name);
		if (it != m_components.end()) return it->second;
		return 0;
	}

	String NameComponentManager::get_name(Entity e) {
		for (auto entry : m_components) {
			if (entry.second == e) return entry.first;
		}
		return "";
	}

	Vector<String> NameComponentManager::get_all_names(Entity e) {
		Vector<String> result;
		for (auto entry : m_components) {
			if (entry.second == e) result.push_back(entry.first);
		}
		return result;
	}

	bool NameComponentManager::add_component(Entity e, String name) {
		return m_components.insert({ name,e }).second;
	}
}