#include "SampleMeekApp.h"

int main()
{
	Meek::ApplicationSpecification appSpec;
	appSpec.Title = "Sample App";
	appSpec.Width = 1280;
	appSpec.Height = 720;
	appSpec.ImGuiConfiguration |= ImGuiConfigFlags_NavEnableKeyboard;
	appSpec.ImGuiConfiguration |= ImGuiConfigFlags_DockingEnable;
	appSpec.ImGuiConfiguration |= ImGuiConfigFlags_ViewportsEnable;

	SampleMeekApp* app = new SampleMeekApp(appSpec);

	app->Run();

	delete app;

	return 0;
}