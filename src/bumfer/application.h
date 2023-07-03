#ifndef BUMFER_APPLICATION_H
#define BUMFER_APPLICATION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application
{
public:
    Application();
    ~Application();

    void Initialise();
    void Run();
    void Dispose();

private:
    GLFWwindow *m_window;
};

#endif // BUMFER_APPLICATION_H