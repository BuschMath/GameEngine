#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <vector>
#include <memory>
#include "SystemBase.h"
#include "SystemRegistry.h"

class SystemManager {
public:
    SystemManager(SystemRegistry& registry) : m_registry(registry) {}

    template<typename T, typename... Args>
    void registerSystem(Args&&... args) {
        static_assert(std::is_base_of<SystemBase, T>::value, "T must be derived from SystemBase");
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        m_systems.push_back(std::move(system));
        m_registry.registerSystem<T>();
    }

    template<typename T>
    void unregisterSystem() {
        static_assert(std::is_base_of<SystemBase, T>::value, "T must be derived from SystemBase");
        auto it = std::find_if(m_systems.begin(), m_systems.end(),
            [](const auto& system) { return dynamic_cast<T*>(system.get()) != nullptr; });
        if (it != m_systems.end()) {
            m_systems.erase(it);
            m_registry.unregisterSystem<T>();
        }
    }

    void update(float deltaTime) {
        for (auto& system : m_systems) {
            system->update(deltaTime);
        }
    }

private:
    SystemRegistry& m_registry;
    std::vector<std::unique_ptr<SystemBase>> m_systems;
};

#endif // !SYSTEM_MANAGER_H

