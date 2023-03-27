#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include "Entity.h"

class EntityManager {
public:
    EntityManager() : m_nextID(0) {}
    Entity createEntity();
    void destroyEntity(Entity entity);
private:
    int m_nextID;
    std::vector<Entity> m_entities;
};

#endif // !ENTITY_MANAGER_H

