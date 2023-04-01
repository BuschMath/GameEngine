#include "Window.h"
#include <iostream>

namespace {
    void errorCallback(int error, const char* description) {
        std::cerr << "GLFW Error: " << description << std::endl;
    }
}

Window::Window(int width, int height, const std::string& title) :
    m_width(width), m_height(height), m_title(title), m_window(nullptr)
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Set the OpenGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }

    // Make the context of the window the main context on the current thread
    glfwMakeContextCurrent(m_window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return;
    }

    // Set the viewport size
    glViewport(0, 0, width, height);

    // Set the error callback function for GLFW
    glfwSetErrorCallback(errorCallback);
}

Window::~Window() {
    // Destroy the window
    glfwDestroyWindow(m_window);

    // Terminate GLFW
    glfwTerminate();
}

bool Window::isOpen() const {
    return !glfwWindowShouldClose(m_window);
}

void Window::update() {
    // Swap the front and back buffers
    glfwSwapBuffers(m_window);

    // Poll for events
    glfwPollEvents();
}

void Window::clear(float r, float g, float b, float a) {
    // Clear the color buffer
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

const std::string& Window::getTitle() const {
    return m_title;
}

GLFWwindow* Window::getWindowHandle() const {
    return m_window;
}

void Window::makeContextCurrent()
{
    glfwMakeContextCurrent(m_window);
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(m_window);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::processInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, true);
    }
}
