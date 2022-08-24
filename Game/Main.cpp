#include "Engine.h"

int main()
{

	//Initialize memory
	InitializeMemory();
	g_renderer.Initialize();
	g_inputSystem.Initialize();
	g_audioSystem.Initialize();
	g_resources.Initialize();
	g_physicsSystem.Initialize();

	neu::Engine::Instance().Register();

	neu::SetFilePath("../Assets");

	g_renderer.CreateWindow("Neumont", 800, 600);
	g_renderer.SetClearColor(neu::Color{0,0,0,255});

	//std::shared_ptr<neu::Texture> texture = neu::g_resources.Get<neu::Texture>("Sprites/Spaceship", &neu::g_renderer);

	//create actors
	neu::Scene scene;

	rapidjson::Document document;
	bool success = neu::json::Load("Models/level.txt", document);
	assert(success);

	scene.Read(document);
	scene.Initialize();

	float angle = 0;

	bool quit = false;

	while (!quit)
	{
		//update (engine)
		neu::g_time.Tick();
		neu::g_inputSystem.Update();
		neu::g_physicsSystem.Update();
		neu::g_audioSystem.Update();

		if (g_inputSystem.GetKeyDown(key_escape)) quit = true;

		//angle += 90.0f * neu::g_time.deltaTime;//rotate

		scene.Update();

		//render
		neu::g_renderer.BeginFrame();//Begin Frame

		scene.Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();//End Frame
	}

	scene.RemoveAll();

	//Shutdown
	//g_inputSystem.ShutDown();
	//g_physicsSystem.ShutDown();
	g_renderer.Shutdown();
	g_audioSystem.Shutdown();
	g_resources.Shutdown();
	g_renderer.Shutdown();
}