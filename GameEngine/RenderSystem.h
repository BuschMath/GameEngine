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

    template<typename T>
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

