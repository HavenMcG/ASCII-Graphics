#include "Transform2dComponent.h"

namespace hecs {

    Transform2dComponent* Transform2dComponentManager::get_component(Entity e) {
        return &m_components[m_map[e]];
    }

    bool Transform2dComponentManager::has_component(Entity e) {
        return (m_map.find(e) != m_map.end());
    }

    void Transform2dComponentManager::add_component(Entity e) {
        int index = m_components.size();
        m_components.push_back(Transform2dComponent{});
        m_map.insert({ e, index });
    }

    void Transform2dComponentManager::remove_component(Entity e) {
        m_components.erase(m_components.begin() + m_map[e]);
        m_map.erase(e);
    }
}