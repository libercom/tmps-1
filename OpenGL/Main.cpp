#define STB_IMAGE_IMPLEMENTATION

#include "src/Application/Application.h"

int main()
{
	Application* app = Application::GetInstance();

	app->Start();
}