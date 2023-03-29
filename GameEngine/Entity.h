#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "Component.h"

class Entity {
public:
    Entity(int id) : m_id(id) {}
    int getID() const { return m_id; }
    bool operator==(Entity right) { return m_id == right.getID(); };

    template <typename T, typename... Args>
    void addComponent(Args&&... args) {
        m_components.emplace_back(new T(std::forward<Args>(args)...));
    }

    template <typename T>
    T* getComponent() {
        for (auto& component : m_components) {
            if (dynamic_cast<T*>(component)) {
                return static_cast<T*>(component);
            }
        }
        return nullptr;
    }

protected:
    std::vector<Component*> m_components;

private:
    int m_id;
};

#endif // !ENTITY_H

