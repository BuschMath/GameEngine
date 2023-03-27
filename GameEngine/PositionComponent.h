#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "Component.h"
#include <type_traits>

template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
class PositionComponent : public Component {
public:
    PositionComponent(T x, T y, T z) : m_x(x), m_y(y), m_z(z) {}

    T x() const { return m_x; }
    T y() const { return m_y; }
    T z() const { return m_z; }

    void setX(T x) { m_x = x; }
    void setY(T y) { m_y = y; }
    void setZ(T z) { m_z = z; }

private:
    T m_x;
    T m_y;
    T m_z;
};



#endif // !POSITION_COMPONENT_H

