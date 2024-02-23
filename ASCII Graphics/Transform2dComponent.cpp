#include "Transform2dComponent.h"

//temp
#include <iostream>

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

    Transform2dComponent* Transform2dComponentManager::add_component(Entity owner) {
        int index = m_components.size();

        Transform2dComponent comp{owner,Coord{},Coord{},-1,-1,-1,-1};

        m_components.push_back(comp);
        m_map.insert({ owner, index });
        return &m_components[index];
    }

    Transform2dComponent* Transform2dComponentManager::add_component(Entity owner, short local_x, short local_y) {
        int index = m_components.size();

        Transform2dComponent comp{ owner,Coord{local_x,local_y},Coord{0,0},-1,-1,-1,-1 };

        m_components.push_back(comp);
        m_map.insert({ owner, index });
        update_world_pos(index, Coord{ local_x,local_y });
        return &m_components[index];
    }

    Transform2dComponent* Transform2dComponentManager::add_component(Entity owner, Entity _parent) {
        Vector<Transform2dComponent>& c = m_components; // for readability
        int index = c.size(); // will become the index of our new component after it is added
        int parent = m_map[_parent];
        //Transform2dComponent& parent_component = c[parent];

        Transform2dComponent comp{ owner, Coord{0,0}, c[parent].world, parent, -1, -1, -1 };
        c.push_back(comp);

        /*std::cout << "\n\nOwning entity: " << c[parent_index].owner << "\n"
            << "local coord: " << c[parent_index].local.x << "," << c[parent_index].local.y << "\n"
            << "world coord: " << c[parent_index].world.x << "," << c[parent_index].world.y << "\n"
            << "Parent: " << c[parent_index].parent << "\n"
            << "First Child: " << c[parent_index].first_child << "\n"
            << "Next Sibling: " << c[parent_index].next_sibling << "\n"
            << "Prev Sibling: " << c[parent_index].prev_sibling << "\n";*/

        // set up pointers
        if (c[parent].first_child == -1) c[parent].first_child = index;
        else {
            Transform2dComponent& sib = c[c[parent].first_child];
            while (sib.next_sibling != -1) {
                sib = c[sib.next_sibling];
            }
            sib.next_sibling = index;
            c[index].prev_sibling = m_map[sib.owner];
        }

        m_map.insert({ owner, index });

        return &c[index];
    }

    Transform2dComponent* Transform2dComponentManager::add_component(Entity owner, Entity parent, short local_x, short local_y) {
        Transform2dComponent* comp = add_component(owner, parent);
        move(owner, Coord{ local_x,local_y });
        return comp;
    }

    void Transform2dComponentManager::remove_component(Entity e) {
        remove_component(m_map[e]);
    }

    void Transform2dComponentManager::remove_component(int index) {
        int& this_i = index;
        Vector<Transform2dComponent>& c = m_components; // for readability
        // handle parent
        if (c[this_i].parent != -1) {
            if (c[c[this_i].parent].first_child == this_i) {
                if (c[this_i].next_sibling == -1) c[c[this_i].parent].first_child = -1;
                else c[c[this_i].parent].first_child = c[this_i].next_sibling;
            }
        }
        // handle prev_sibling
        if (c[this_i].prev_sibling != -1) {
            if (c[this_i].next_sibling == -1) c[c[this_i].prev_sibling].next_sibling = -1;
            else c[c[this_i].prev_sibling].next_sibling = c[this_i].next_sibling;
        }
        // handle next_sibling
        if (c[this_i].next_sibling != -1) {
            if (c[this_i].prev_sibling == -1) c[c[this_i].next_sibling].prev_sibling = -1;
            else c[c[this_i].next_sibling].prev_sibling = c[this_i].prev_sibling;
        }
        // handle children
        while (c[this_i].first_child != -1) {
            remove_component(c[this_i].first_child);
        }
        m_components.erase(m_components.begin() + m_map[c[this_i].owner]);
        m_map.erase(c[this_i].owner);
    }

    void Transform2dComponentManager::move(Entity e, Coord change) {
        int this_i = m_map[e];
        Vector<Transform2dComponent>& c = m_components; // for readability
        c[this_i].local = c[this_i].local + change;
        c[this_i].world = c[this_i].world + change;

        int child = c[this_i].first_child;
        while (child != -1) {
            update_world_pos(child, change);
            child = c[child].next_sibling;
        }
    }

    void Transform2dComponentManager::update_world_pos(int index, Coord change) {
        int& this_i = index;
        Vector<Transform2dComponent>& c = m_components; // for readability
        c[this_i].world = c[this_i].world + change;

        int child = c[this_i].first_child;
        while (child != -1) {
            update_world_pos(child, change);
            child = c[child].next_sibling;
        }
    }
}