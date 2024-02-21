#include "EntityManager.h"

namespace hecs {
	
	int EntityManager::create_entity() {
		m_entities.push_back(m_next_entity);
		++m_next_entity;
		// TODO: Check if reached max entities
		return true;
	}
}
