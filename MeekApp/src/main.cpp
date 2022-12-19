#include "Core/Application.h"

class SampleMeekApp final : public Meek::Application
{
	using Meek::Application::Application;
};

int main()
{
	SampleMeekApp* app = new SampleMeekApp("My Meek App", 1280, 720);
	app->Run();

	delete app;

	return 0;
}