#include "SpriteComponent.h"

namespace hecs {

    SpriteComponent* SpriteComponentManager::get_component(Entity e) {
        return &m_components[m_map[e]];
    }

    const Vector<SpriteComponent>& SpriteComponentManager::components() {
        return m_components;
    }

    bool SpriteComponentManager::has_component(Entity e) {
        return (m_map.find(e) != m_map.end());
    }

    void SpriteComponentManager::add_component(Entity e) {
        int index = m_components.size();
        SpriteComponent comp{};
        comp.owner = e;
        m_components.push_back(comp);
        m_map.insert({ e, index });
    }

    void SpriteComponentManager::remove_component(Entity e) {
        m_components.erase(m_components.begin() + m_map[e]);
        m_map.erase(e);
    }
}