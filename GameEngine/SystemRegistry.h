#ifndef SYSTEM_REGISTRY_H
#define SYSTEM_REGISTRY_H

#include <map>
#include <memory>
#include <typeindex>
#include "SystemBase.h"

class SystemRegistry {
public:
    template<typename T>
    void registerSystem() {
        static_assert(std::is_base_of<SystemBase, T>::value, "T must be derived from SystemBase");
        m_systems[std::type_index(typeid(T))] = std::make_unique<T>();
    }

    template<typename T>
    T* getSystem() const {
        auto it = m_systems.find(std::type_index(typeid(T)));
        if (it == m_systems.end()) {
            return nullptr;
        }
        return dynamic_cast<T*>(it->second.get());
    }

private:
    std::map<std::type_index, std::unique_ptr<SystemBase>> m_systems;
};

#endif // !SYSTEM_REGISTRY_H

