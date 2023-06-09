#include "GameEngine.h"

GameEngine::GameEngine(int width, int height, const char* title)
    : m_window(width, height, title)
{   
}

GameEngine::GameEngine()
    : m_window(800, 600, "GameEngine"), m_running(false)
{
}

GameEngine::~GameEngine()
{
    for (auto system : m_systems) {
        delete system;
    }
}

void GameEngine::update(float deltaTime)
{
    m_messagingSystem->update(deltaTime);
    m_renderSystem->update(deltaTime);
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
    m_entityFactory = std::make_unique<ConcreteEntityFactory<Component>>();
    m_componentManager = std::make_unique<ComponentManager>();

    // Render system
    m_renderSystem = std::make_unique<RenderSystem>();

    // Create systems and add them to the system list

    // Initialize each system
    m_messagingSystem = std::make_unique<MessagingSystem>();
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
}

void GameEngine::cleanup()
{
    // Cleanup systems and entities
}