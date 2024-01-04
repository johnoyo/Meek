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
    Application* Application::s_Instance = nullptr;

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

        s_Instance = this;
    }

    Application::~Application()
    {
        s_Instance = nullptr;

        OnDetach();
        Clean();
    }

    Application& Application::Get()
    {
        return *s_Instance;
    }

    GLFWwindow* Application::GetWindow()
    {
        return m_Window;
    }

    void Application::Run()
    {
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        ImGuiRenderer::Get().Initialize(m_Window, m_Specification.DarkMode, m_Specification.ImGuiConfiguration);

        OnAttach();

        // Main loop
        while (!glfwWindowShouldClose(m_Window))
        {
            BeginFrame();

            OnUpdate(m_DeltaTime);
            
            ImGuiRenderer::Get().BeginFrame();

            OnGUIRender(m_DeltaTime);

            ImGuiRenderer::Get().EndFrame();

            EndFrame();
        }
    }

    void Application::SetTitle(const std::string& title)
    {
        m_Specification.Title = title;
        glfwSetWindowTitle(m_Window, title.c_str());
    }

    double Application::GetTime()
    {
        return glfwGetTime();
    }

    void Application::Close()
    {
        glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
    }

    void Application::BeginFrame()
    {
        float time = (float)glfwGetTime();
        m_DeltaTime = time - m_LastTime;
        m_FixedDeltaTime += (time - m_LastTime) / m_LimitFPS;
        m_LastTime = time;
    }

    void Application::EndFrame()
    {
        m_Frames++;

        // Reset after one second.
        if (glfwGetTime() - m_Timer > 1.0)
        {
            if (m_Specification.ShowFPS)
            {
                // Display frame rate at window bar.
                std::stringstream ss;
                ss << m_Specification.Title << " [" << m_Frames << " FPS]";
                glfwSetWindowTitle(m_Window, ss.str().c_str());
            }

            m_Timer++;
            m_Frames = 0;
            m_FixedUpdates = 0;
        }
    }

    void Application::Clean()
    {
        ImGuiRenderer::Get().Clean();

        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
}
