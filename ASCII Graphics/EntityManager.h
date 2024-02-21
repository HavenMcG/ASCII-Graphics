#pragma once

#include "HECS.h"

namespace hecs {

	class EntityManager {
	public:
		int create_entity();

	private:
		Vector<Entity> m_entities;
		Entity m_next_entity = 0;
	};
}