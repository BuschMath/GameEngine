#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm.hpp>
#include <string>
#include "ShaderProgram.h"

class Material {
public:
    Material(const std::string& texturePath, glm::vec3 baseColor, ShaderProgram* shaderProgram,
        float shininess)
        : m_texturePath(texturePath), m_color(baseColor), m_shaderProgram(shaderProgram), 
        m_shininess(shininess) {}

    const std::string& getTexturePath() const { return m_texturePath; }
    void setTexturePath(const std::string& texturePath) { m_texturePath = texturePath; }
    glm::vec3 getBaseColor() { return m_color; }
    void setColor(glm::vec3 color) { m_color = color; }

    ShaderProgram* getShaderProgram() const { return m_shaderProgram; }
    void setShaderProgram(ShaderProgram* shaderProgram) { m_shaderProgram = shaderProgram; }

    float getShininess() const { return m_shininess; }
    void setShininess(float shininess) { m_shininess = shininess; }

private:
    glm::vec3 m_color;
    std::string m_texturePath;
    ShaderProgram* m_shaderProgram;
    float m_shininess;
};

#endif // !MATERIAL_H

