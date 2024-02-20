#include "EntityManager.h"

namespace hecs {
	Entity NameComponentManager::find(std::string name) {
		auto it = m_components.find(name);
		if (it != m_components.end()) return it->second;
		return 0;
	}

	std::string NameComponentManager::get_name(Entity e) {
		for (auto entry : m_components) {
			if (entry.second == e) return entry.first;
		}
		return "";
	}

	std::vector<std::string> NameComponentManager::get_all_names(Entity e) {
		std::vector<std::string> result;
		for (auto entry : m_components) {
			if (entry.second == e) result.push_back(entry.first);
		}
		return result;
	}

	bool NameComponentManager::add_component(Entity e, std::string name) {
		return m_components.insert({name,e}).second;
	}

	int EntityManager::create_entity() {
		m_entities.push_back(m_next_entity);
		++m_next_entity;
		// TODO: Check if reached max entities
		return true;
	}

}
