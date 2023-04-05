#include "GameEngine.h"

GameEngine::GameEngine(int width, int height, const char* title)
    : m_window(width, height, title)
{
    // Initialize systems
    m_renderSystem = std::make_unique<RenderSystem>();
    m_messagingSystem = std::make_unique<MessagingSystem>();
}

GameEngine::GameEngine()
    : m_window(800, 600, "GameEngine"), m_running(false)
{
    m_entities.reserve(100);
    m_systems.reserve(10);
}

GameEngine::~GameEngine()
{
    for (auto entity : m_entities) {
        delete entity;
    }

    for (auto system : m_systems) {
        delete system;
    }
}

void GameEngine::run() 
{
    // Set up game loop
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    while (!m_window.shouldClose()) {
        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentFrameTime - lastFrameTime).count();

        // Handle input
        processInput(deltaTime);

        // Update game state
        update(deltaTime);

        // Render game
        render();

        lastFrameTime = currentFrameTime;

        // Wait for next frame
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void GameEngine::initialize()
{
    // Create entities and add them to the entity list

    // Create systems and add them to the system list

    // Initialize each system
}

void GameEngine::processInput(float deltaTime)
{
    m_window.processInput();
}

void GameEngine::render()
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render systems
    m_renderSystem->render();

    // Swap buffers
    m_window.swapBuffers();
}

void GameEngine::cleanup()
{
    // Cleanup systems and entities
}