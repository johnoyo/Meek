#pragma once

#include "imgui.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Image.h"

namespace Meek {

	class Application
	{
	public:
		Application(const std::string& title, int width, int height, bool VSync = true, bool darkMode = true);
		~Application();

		virtual void OnAttach()    {};
		virtual void OnUpdate()    {};
		virtual void OnRender()    {};
		virtual void OnGUIRender() {};
		virtual void OnDetach()    {};

		void Run();

	private:
		GLFWwindow* m_Window;
		const std::string& m_Title;
		int m_Width = 1280;
		int m_Height = 720;
		bool m_Darkmode;
		bool m_VSync;

		const char* m_GlslVersion;
		ImGuiIO m_IO;

		void InitializeGLFW();
		void InitializeIMGUI();
		void InitializeBackends();
		void Clean();
	};

}