#include "Application.h"

#include <GLM/glm.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

namespace Meek
{
    Application::Application(ApplicationSpecification& spec)
        : m_Specification(spec)
    {
        // Setup window
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
            return;

        // Create window with graphics context
        m_Window = glfwCreateWindow(m_Specification.Width, m_Specification.Height, m_Specification.Title.c_str(), NULL, NULL);
        if (m_Window == NULL)
            return;

        glfwMakeContextCurrent(m_Window);

        if (m_Specification.Vsync)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }

    Application::~Application()
    {
        OnDetach();
        Clean();
    }

    void Application::Run()
    {
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        ImGuiRenderer::Get().Initialize(m_Window, m_Specification.DarkMode, m_Specification.ImGuiConfiguration);

        OnAttach();

        // Main loop
        while (!glfwWindowShouldClose(m_Window))
        {
            OnUpdate();
            
            ImGuiRenderer::Get().BeginFrame();

            OnGUIRender();

            ImGuiRenderer::Get().EndFrame();
        }
    }

    void Application::Clean()
    {
        // Cleanup
        ImGuiRenderer::Get().Clean();

        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
}
