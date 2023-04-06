#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "SystemBase.h"
#include "Entity.h"
#include "Window.h"
#include "PositionComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

class RenderSystem : public SystemBase {
public:
    RenderSystem() : m_window(*(new Window(800, 600, "Void"))){
        r = new Renderer();
        m_camera = new Camera();
    }

    RenderSystem(Window& window) : m_window(window) {
        r = new Renderer();
        m_camera = new Camera();
    }

    void update(float deltaTime) override {
        render();
        /*glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up the camera view matrix
        glm::mat4 viewMatrix = m_camera->getViewMatrix();

        // Set up the projection matrix
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(m_camera->getFOV()),
            float(m_window.getWidth() / m_window.getHeight()), 0.1f, 100.0f);

        // Loop through all the entities and render them
        for (auto& entity : m_entities) {
            // Get the render component for this entity
            RenderComponent* renderComponent = entity->getComponent<RenderComponent>();

            // If the entity has a render component
            if (renderComponent) {
                // Bind the material
                renderComponent->getMaterial()->getShaderProgram()->bind();

                // Bind the mesh
                renderComponent->getMesh()->bind();

                // Set the model matrix
                glm::mat4 modelMatrix = glm::mat4(1.0f);
                modelMatrix = glm::translate(modelMatrix, renderComponent->getPosition());
                modelMatrix = glm::rotate(modelMatrix, glm::radians(renderComponent->getRotation().x), glm::vec3(1, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(renderComponent->getRotation().y), glm::vec3(0, 1, 0));
                modelMatrix = glm::rotate(modelMatrix, glm::radians(renderComponent->getRotation().z), glm::vec3(0, 0, 1));
                modelMatrix = glm::scale(modelMatrix, renderComponent->getScale());

                // Set the uniforms in the shader program
                renderComponent->getMaterial()->getShaderProgram()->setUniformMat4("model", modelMatrix);
                renderComponent->getMaterial()->getShaderProgram()->setUniformMat4("view", viewMatrix);
                renderComponent->getMaterial()->getShaderProgram()->setUniformMat4("projection", projectionMatrix);

                // Draw the mesh
                renderComponent->getMesh()->draw();
            }
        }*/

        // Swap buffers
        //m_window.update();
    }

    void render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        for (auto& entity : m_entities) {
            if (entity->getComponent<RenderComponent>() != nullptr) {
                // get the RenderComponent for the entity
                RenderComponent* renderComponent = entity->getComponent<RenderComponent>();

                r->render(renderComponent);
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
    Renderer* r;
    Camera* m_camera;
};

#endif // !RENDER_SYSTEM_H

