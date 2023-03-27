#ifndef SYSTEM_FACTORY_H
#define SYSTEM_FACTORY_H

#include "SystemBase.h"
#include <memory>
#include <type_traits>
#include <utility>

class SystemFactory {
public:
    template<typename T, typename... Args>
    std::unique_ptr<T> createSystem(Args&&... args) {
        static_assert(std::is_base_of<SystemBase, T>::value, "T must inherit from SystemBase");
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
};

#endif // !SYSTEM_FACTORY_H

