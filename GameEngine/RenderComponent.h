#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Component.h"
#include <string>
#include <glm.hpp>
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"

class RenderComponent : public Component {
private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    Material* m_material;
    Mesh* m_mesh;
    Texture* m_texture;

public:
    RenderComponent() :
        m_position(glm::vec3(0.0f)),
        m_rotation(glm::vec3(0.0f)),
        m_scale(glm::vec3(1.0f)),
        m_material(nullptr),
        m_mesh(nullptr),
        m_texture(nullptr)
    {}

    RenderComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, 
        Material* material, Mesh* mesh, Texture* texture) :
        m_position(position),
        m_rotation(rotation),
        m_scale(scale),
        m_material(material),
        m_mesh(mesh),
        m_texture(texture)
    {}

    // Getters
    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getRotation() const { return m_rotation; }
    glm::vec3 getScale() const { return m_scale; }
    Material* getMaterial() const { return m_material; }
    Mesh* getMesh() const { return m_mesh; }
    Texture* getTexture() const { return m_texture; }

    // Setters
    void setPosition(glm::vec3 position) { m_position = position; }
    void setRotation(glm::vec3 rotation) { m_rotation = rotation; }
    void setScale(glm::vec3 scale) { m_scale = scale; }
    void setMaterial(Material* material) { m_material = material; }
    void setMesh(Mesh* mesh) { m_mesh = mesh; }
    void setTexture(Texture* texture) { m_texture = texture; }
};

#endif // !RENDER_COMPONENT_H

