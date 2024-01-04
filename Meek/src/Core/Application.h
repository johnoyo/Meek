#pragma once

#include "Image.h"
#include "ImGuiRenderer.h"

#include "Dialog.h"

#include "Random.h"

#include <imgui.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <sstream>

namespace Meek 
{
	struct ApplicationSpecification
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		bool Vsync = true;
		bool DarkMode = true;
		bool ShowFPS = true;
		ImGuiConfigFlags ImGuiConfiguration = 0;
	};

	class Application
	{
	public:
		Application(ApplicationSpecification& spec);
		~Application();

		static Application& Get();

		GLFWwindow* GetWindow();

		virtual void OnAttach()            {};
		virtual void OnUpdate(float ts)    {};
		virtual void OnGUIRender(float ts) {};
		virtual void OnDetach()            {};

		void Run();

		void SetTitle(const std::string& title);
		double GetTime();
		void Close();

	private:
		void BeginFrame();
		void EndFrame();
		void Clean();

	private:
		static Application* s_Instance;

		GLFWwindow* m_Window = nullptr;
		ApplicationSpecification m_Specification;

		float m_LastTime = 0.0f;
		float m_Timer = m_LastTime;
		float m_DeltaTime = 0.0f;
		int m_Frames = 0, m_Updates = 0;

		float m_LimitFPS = 1.0f / 60.0f;
		float m_FixedDeltaTime = 0.0f;
		int m_FixedUpdates = 0;
	};
}