#include "Engine.h"

#include <iostream>

int main()
{
	std::cout << "hello world!\n";

	neu::SetFilePath("../Assets");

	//Initialize memory
	InitializeMemory();
	g_renderer.Initialize();
	g_inputSystem.Initialize();

	g_renderer.CreateWindow("Neumont", 800, 600);

	bool quit = false;

	while (!quit)
	{
		//update (engine)
		neu::g_inputSystem.Update();
		//neu::g_audioSystems.Update;

		if (g_inputSystem.GetKeyDown(key_escape)) quit = true;

		neu::g_renderer.BeginFrame();

		neu::g_renderer.EndFrame();
	}

	//Shutdown
	//g_inputSystem.ShutDown;
	g_renderer.Shutdown();
	//g_audioSystem.Shutdown();
}