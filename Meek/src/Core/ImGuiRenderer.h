#pragma once

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace Meek
{
	class ImGuiRenderer
	{
	public:
		ImGuiRenderer(const ImGuiRenderer&) = delete;

		static ImGuiRenderer& Get()
		{
			static ImGuiRenderer instance;
			return instance;
		}

		void Initialize(GLFWwindow* window, bool darkMode, ImGuiConfigFlags imGuiConfigFlags);

		void BeginFrame();
		void EndFrame();

		void Clean();

	private:
		ImGuiRenderer() {}

		GLFWwindow* m_Window = nullptr;
		const char* m_GlslVersion = nullptr;
	};
}