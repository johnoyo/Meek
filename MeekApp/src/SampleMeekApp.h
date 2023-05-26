#pragma once

#include "Core/Application.h"

class SampleMeekApp final : public Meek::Application
{
    using Meek::Application::Application;

    virtual void OnAttach() override;
    virtual void OnGUIRender() override;

    uint32_t* data = nullptr;

    bool show_demo_window = false;

    Meek::Image customImg = Meek::Image(250.0f, 250.0f, data);
    Meek::Image img = Meek::Image("assets/cute-animal-illustration.jpg");
};