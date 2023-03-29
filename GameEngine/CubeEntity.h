#ifndef CUBE_ENTITY_H
#define CUBE_ENTITY_H

#include "Entity.h"
#include "PositionComponent.h"
#include "RenderComponent.h"

class CubeEntity : public Entity {
public:
    template <typename T>
    CubeEntity(int id, T x, T y, T z, float size, const std::string& texturePath) : Entity(id)
    {
        addComponent<PositionComponent>(x, y, z);
        addComponent<RenderComponent>(size, texturePath);
    }
};

#endif // !CUBE_ENTITY_H

