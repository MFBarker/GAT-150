#include "Engine.h"
#include "MyGame.h"

int main()
{

	//Initialize memory
	InitializeMemory();
	g_renderer.Initialize();
	g_inputSystem.Initialize();
	g_audioSystem.Initialize();
	g_resources.Initialize();
	g_physicsSystem.Initialize();
	g_eventManager.Initialize();

	neu::Engine::Instance().Register();

	neu::SetFilePath("../Assets");

	g_renderer.CreateWindow("Neumont", 800, 600);
	g_renderer.SetClearColor(neu::Color{0,0,0,255});

	//std::shared_ptr<neu::Texture> texture = neu::g_resources.Get<neu::Texture>("Sprites/Spaceship", &neu::g_renderer);

	//create Game
	std::unique_ptr<MyGame> game = std::make_unique<MyGame>();
	game->Initialize();

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

		game->Update();

		//render
		neu::g_renderer.BeginFrame();//Begin Frame

		game->Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();//End Frame
	}

	game->Shutdown();
	game.reset();
	neu::Factory::Instance().Shutdown();

	//Shutdown
	g_inputSystem.Shutdown();
	g_physicsSystem.Shutdown();
	g_renderer.Shutdown();
	g_audioSystem.Shutdown();
	g_resources.Shutdown();
	g_renderer.Shutdown();
	g_eventManager.Shutdown();
}