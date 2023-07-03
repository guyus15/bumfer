#include <bumfer/application.h>

#include <iostream>

Application::Application()
    : m_window{nullptr}
{
    Initialise();
}

Application::~Application()
{
    Dispose();
}

void Application::Initialise()
{
    if (!glfwInit())
    {
        std::cout << "Error: Failed to initialise GLFW\n";
    }

    m_window = glfwCreateWindow(
        640,
        480,
        "Bumfer",
        nullptr,
        nullptr);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    if (!m_window)
    {
        std::cout << "Error: Failed to initialise GLFW window.\n";
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Error: Failed to initialise GLAD.\n";
    }
}

void Application::Run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }
}

void Application::Dispose()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}