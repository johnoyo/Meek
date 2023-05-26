#include "SampleMeekApp.h"

void SampleMeekApp::OnAttach()
{
    data = new uint32_t[250 * 250 * sizeof(uint32_t)];

    for (int i = 0; i < 250 * 250; i++)
        data[i] = 0xffffffff;

    customImg.Invalidate(data);
}

void SampleMeekApp::OnGUIRender()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    {
        ImGui::Begin("Panel 0");

        ImGui::Image(img.GetID(), ImVec2(img.GetWidth(), img.GetHeight()));

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    {
        static int counter = 0;

        ImGui::Begin("Panel 1");

        ImGui::Text("Pick a color");

        if (ImGui::Button("Red"))
        {
            for (int i = 0; i < 250 * 250; i++)
                data[i] = 0xff0000ff;

            customImg.Invalidate(data);
            counter++;
        }

        if (ImGui::Button("Magenta"))
        {
            for (int i = 0; i < 250 * 250; i++)
                data[i] = 0xffff00ff;

            customImg.Invalidate(data);
            counter++;
        }

        ImGui::Image(customImg.GetID(), ImVec2(customImg.GetWidth(), customImg.GetHeight()));

        ImGui::Text("Color button counter = %d", counter);

        ImGui::Checkbox("Demo Window", &show_demo_window);

        ImGui::End();
    }
}