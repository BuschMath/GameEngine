#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <unordered_map>
#include <typeindex>
#include <memory>
#include "Component.h"
#include "Entity.h"

class ComponentManager {
public:
    template<typename T>
    void addComponent(Entity entity, T&& component);
    template<typename T>
    void removeComponent(Entity entity);
    template<typename T>
    T* getComponent(Entity entity);
private:
    std::unordered_map<Entity, std::unordered_map<std::size_t, std::unique_ptr<Component>>> m_components;
};

template<typename T>
void ComponentManager::addComponent(Entity entity, T&& component) {
    auto typeId = typeid(T).hash_code();
    auto& entityComponents = m_components[entity];
    entityComponents[typeId] = std::make_unique<T>(std::forward<T>(component));
}

template<typename T>
void ComponentManager::removeComponent(Entity entity) {
    auto typeId = typeid(T).hash_code();
    auto& entityComponents = m_components[entity];
    entityComponents.erase(typeId);
}

template<typename T>
T* ComponentManager::getComponent(Entity entity) {
    auto typeId = typeid(T).hash_code();
    auto& entityComponents = m_components[entity];
    auto it = entityComponents.find(typeId);
    if (it != entityComponents.end()) {
        return dynamic_cast<T*>(it->second.get());
    }
    return nullptr;
}


#endif // !COMPONENT_MANAGER_H

