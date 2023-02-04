#include "SampleMeekApp.h"

int main()
{
	SampleMeekApp* app = new SampleMeekApp("My Meek App", 1280, 720);
	app->Run();

	delete app;

	return 0;
}