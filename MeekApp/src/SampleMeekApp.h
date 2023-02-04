#pragma once

#include "Core/Application.h"

class SampleMeekApp final : public Meek::Application
{
    using Meek::Application::Application;

    uint32_t* data = nullptr;

    bool show_another_window = false;
    bool show_demo_window = true;

    Meek::Image customImg = Meek::Image(250.0f, 250.0f, data);
    Meek::Image img = Meek::Image("src/AButton.png");

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    virtual void OnAttach()
    {
        data = new uint32_t[250 * 250 * sizeof(uint32_t)];
    }

    virtual void OnGUIRender()
    {
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Image(img.GetID(), ImVec2(img.GetWidth(), img.GetHeight()));

            if (ImGui::Button("Red"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            {
                for (int i = 0; i < 250 * 250; i++)
                    data[i] = 0xff0000ff;

                customImg.Invalidate(data);
                counter++;
            }

            if (ImGui::Button("Magenta"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            {
                for (int i = 0; i < 250 * 250; i++)
                    data[i] = 0xffff00ff;

                customImg.Invalidate(data);
                counter++;
            }

            ImGui::Image(customImg.GetID(), ImVec2(customImg.GetWidth(), customImg.GetHeight()));

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
    }
};