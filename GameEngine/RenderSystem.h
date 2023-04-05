#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "SystemBase.h"
#include "Entity.h"
#include "Window.h"
#include "PositionComponent.h"
#include "RenderComponent.h"
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

class RenderSystem : public SystemBase {
public:
    RenderSystem(Window& window) : m_window(window) {}

    template <typename T>
    void update(float deltaTime) override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& entity : m_entities) {
            auto position = entity->getComponent<PositionComponent>();
            auto render = entity->getComponent<RenderComponent>();

            if (position && render) {
                glPushMatrix();
                glTranslatef(position->x, position->y, position->z);

                glBindTexture(GL_TEXTURE_2D, render->texture);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(-render->size, -render->size, -render->size);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(render->size, -render->size, -render->size);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(render->size, render->size, -render->size);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(-render->size, render->size, -render->size);
                glEnd();

                glPopMatrix();
            }
        }

        glfwSwapBuffers(m_window.getWindow());
        glfwPollEvents();
    }

    void render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        for (auto& entity : m_entities) {
            if (entity->getComponent<RenderComponent>() != nullptr) {
                // get the RenderComponent for the entity
                RenderComponent* renderComponent = entity->getComponent<RenderComponent>();

                // bind the shader program
                renderComponent->getMaterial()->getShaderProgram()->bind();

                // set the material properties
                renderComponent->getMaterial()->setUniformVec3("material.color", renderComponent->getColor());
                renderComponent->getMaterial()->setUniformFloat("material.shininess", renderComponent->getShininess());

                // set the transformation matrices
                glm::mat4 modelMatrix = entity->getTransform().getModelMatrix();
                glm::mat4 viewMatrix = m_camera.getViewMatrix();
                glm::mat4 projectionMatrix = m_camera.getProjectionMatrix();
                renderComponent->getMaterial()->setUniformMat4("modelMatrix", modelMatrix);
                renderComponent->getMaterial()->setUniformMat4("viewMatrix", viewMatrix);
                renderComponent->getMaterial()->setUniformMat4("projectionMatrix", projectionMatrix);

                // bind the vertex array object
                glBindVertexArray(renderComponent->getMesh()->getVAO());

                // draw the mesh
                glDrawElements(GL_TRIANGLES, renderComponent->getMesh()->getNumIndices(), GL_UNSIGNED_INT, 0);

                // unbind the vertex array object
                glBindVertexArray(0);
            }
        }

        m_window.swapBuffers();
    }

    void addEntity(Entity* entity) {
        m_entities.emplace_back(entity);
    }

    void removeEntity(Entity* entity) {
        m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
            [&](const auto& e) { return e == entity; }), m_entities.end());
    }

private:
    Window& m_window;
    std::vector<Entity*> m_entities;
};

#endif // !RENDER_SYSTEM_H

