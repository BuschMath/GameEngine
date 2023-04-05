#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "SystemBase.h"
#include "Entity.h"
#include "Window.h"
#include "PositionComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

class RenderSystem : public SystemBase {
public:
    RenderSystem(Window& window) : m_window(window) {
        r = new Renderer();
    }

    void update(float deltaTime) override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& entity : m_entities) {
            auto position = entity->getComponent<PositionComponent<float>>();
            auto render = entity->getComponent<RenderComponent>();

            if (position && render) {
                glPushMatrix();
                glTranslatef(position->x(), position->y(), position->z());

                render->getTexture()->bind();
                glBindTexture(GL_TEXTURE_2D, render->getTexture()->getId());
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
};

#endif // !RENDER_SYSTEM_H

