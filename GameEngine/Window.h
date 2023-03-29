#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();
    void makeContextCurrent();
    bool shouldClose();
    void swapBuffers();
    void pollEvents();
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    void update();
    bool isOpen() const;
    void clear(float r, float g, float b, float a);
    const std::string& getTitle() const;
    GLFWwindow* getWindowHandle() const;

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;
};

#endif // !WINDOW_H
