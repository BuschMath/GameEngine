#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

#include <unordered_map>
#include <functional>
#include <memory>
#include "Component.h"

class ComponentFactory {
public:
    template<typename T>
    void registerComponent();
    std::unique_ptr<Component> createComponent(std::size_t componentTypeId);
private:
    std::unordered_map<std::size_t, std::function<std::unique_ptr<Component>()>> m_componentFactories;
};

template<typename T>
void ComponentFactory::registerComponent() {
    auto typeId = typeid(T).hash_code();
    m_componentFactories[typeId] = []() { return std::make_unique<T>(); };
}

std::unique_ptr<Component> ComponentFactory::createComponent(std::size_t componentTypeId) {
    auto it = m_componentFactories.find(componentTypeId);
    if (it != m_componentFactories.end()) {
        return it->second();
    }
    return nullptr;
}


#endif // !COMPONENT_FACTORY_H
