#include <bumfer/application.h>

#include <bumfer/widgets/widget_manager.h>
#include <bumfer/widgets/time_date_widget.h>

#include "imgui.cpp"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);

    if (!m_window)
    {
        std::cout << "Error: Failed to initialise GLFW window.\n";
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Error: Failed to initialise GLAD.\n";
    }

    // Setup Dear ImGui context.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 120");

    WidgetManager::Initialise();
}

void Application::Run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        WidgetManager::Update();

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (WidgetManager::HasWidget<TimeDateWidget>())
        {
            const TimeDateWidget *time_date_widget = WidgetManager::GetWidget<TimeDateWidget>();

            ImGui::Begin("Time & Date");

            ImGui::Text("%s", time_date_widget->GetDateString().c_str());
            ImGui::Text("%s", time_date_widget->GetTimeString().c_str());

            ImGui::End();
        }

        ImGui::Begin("Spotify");

        ImGui::End();

        ImGui::ShowDemoWindow();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);
    }
}

void Application::Dispose()
{
    WidgetManager::Dispose();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}