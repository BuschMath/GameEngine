#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Component.h"
#include <string>

class RenderComponent : public Component {
public:
    RenderComponent(const std::string& texturePath)
        : m_texturePath(texturePath) {}

    const std::string& getTexturePath() const { return m_texturePath; }

private:
    std::string m_texturePath;
};

#endif // !RENDER_COMPONENT_H

