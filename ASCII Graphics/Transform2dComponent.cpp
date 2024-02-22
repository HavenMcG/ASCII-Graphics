#include "Transform2dComponent.h"

namespace hecs {

    Transform2dComponent* Transform2dComponentManager::get_component(Entity e) {
        return &m_components[m_map[e]];
    }

    const Vector<Transform2dComponent>& Transform2dComponentManager::components() {
        return m_components;
    }

    bool Transform2dComponentManager::has_component(Entity e) {
        return (m_map.find(e) != m_map.end());
    }

    Transform2dComponent* Transform2dComponentManager::add_component(Entity e) {
        int index = m_components.size();
        Transform2dComponent comp{};
        comp.owner = e;
        m_components.push_back(comp);
        m_map.insert({ e, index });
        return &m_components[index];
    }

    Transform2dComponent* Transform2dComponentManager::add_component(Entity e, short x, short y) {
        int index = m_components.size();
        Transform2dComponent comp{ e,x,y };
        m_components.push_back(comp);
        m_map.insert({ e, index });
        return &m_components[index];
    }

    void Transform2dComponentManager::remove_component(Entity e) {
        m_components.erase(m_components.begin() + m_map[e]);
        m_map.erase(e);
    }
}