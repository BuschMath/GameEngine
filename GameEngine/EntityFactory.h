#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <vector>
#include <memory>
#include "Entity.h"
#include "Component.h"
#include "ComponentFactory.h"
#include "EntityManager.h"

class EntityFactory {
public:
    virtual ~EntityFactory() {}

    virtual std::unique_ptr<Entity> createEntity() = 0;
};

template<typename T>
class ConcreteEntityFactory : public EntityFactory {
public:
    ConcreteEntityFactory(ComponentFactory& componentFactory, EntityManager& entityManager)
        : m_componentFactory(componentFactory), m_entityManager(entityManager) {}

    std::unique_ptr<Entity> createEntity() override {
        auto entity = std::make_unique<Entity>();
        m_entityManager.addEntity(entity.get());
        addComponents(entity.get());
        return entity;
    };

private:
    void addComponents(Entity* entity) {
        for (auto componentTypeId : T::getComponentTypeIds()) {
            auto component = m_componentFactory.createComponent(componentTypeId);
            if (component) {
                entity->addComponent(std::move(component));
            }
        }
    }

    ComponentFactory& m_componentFactory;
    EntityManager& m_entityManager;
};


#endif // !ENTITY_FACTORY_H
