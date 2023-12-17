#pragma once

#include "Image.h"
#include "ImGuiRenderer.h"

#include "Dialog.h"

#include <imgui.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Meek 
{
	struct ApplicationSpecification
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		bool Vsync = true;
		bool DarkMode = true;
		ImGuiConfigFlags ImGuiConfiguration = 0;
	};

	class Application
	{
	public:
		Application(ApplicationSpecification& spec);
		~Application();

		virtual void OnAttach()    {};
		virtual void OnUpdate()    {};
		virtual void OnGUIRender() {};
		virtual void OnDetach()    {};

		void Run();

	private:
		GLFWwindow* m_Window = nullptr;
		ApplicationSpecification m_Specification;

		void Clean();
	};
}