#include "EntityManager.h"

Entity EntityManager::createEntity() {
    Entity entity(m_nextID++);
    m_entities.push_back(entity);
    return entity;
}

void EntityManager::destroyEntity(Entity entity) {
    // Find and remove the entity from the list
    for (auto it = m_entities.begin(); it != m_entities.end(); ++it) {
        if (*it == entity) {
            m_entities.erase(it);
            break;
        }
    }
}