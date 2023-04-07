#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Window.h"
#include "EntityFactory.h"
#include "ComponentManager.h"
#include "SystemBase.h"
#include "RenderSystem.h"
#include "MessagingSystem.h"

#include <chrono>
#include <thread>

class GameEngine {
public:
    GameEngine();
    GameEngine(int width, int height, const char* title);
    ~GameEngine();

    void initialize();
    void run();
    void cleanup();

private:
    void processInput(float deltaTime);

    void update(float deltaTime);

    void render();

    Window m_window;
    std::unique_ptr<RenderSystem> m_renderSystem;
    std::unique_ptr<MessagingSystem> m_messagingSystem;
    std::unique_ptr<ConcreteEntityFactory<Component>> m_entityFactory;
    std::unique_ptr<ComponentManager> m_componentManager;
    std::vector<SystemBase*> m_systems;
    bool m_running;
};


#endif // !GAME_ENGINE_H
