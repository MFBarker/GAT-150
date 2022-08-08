#include "Engine.h"

#include <iostream>



int main()
{
	//Initialize memory
	InitializeMemory();
	g_renderer.Initialize();
	g_inputSystem.Initialize();
	//g_audioSystem.Initialize();

	neu::SetFilePath("../Assets");

	g_renderer.CreateWindow("Neumont", 800, 600);
	g_renderer.SetClearColor(neu::Color{0,0,0,255});

	//create Texture
	std::shared_ptr<neu::Texture> texture = std::make_shared<neu::Texture>();
	//texture->Create(neu::g_renderer, "sf2.png");
	//texture->Create(neu::g_renderer, "HeadEmpty.png");
	texture->Create(neu::g_renderer, "Sprites/SpaceShip.png");

	g_audioSystem.AddAudio("temp", "Audio/fart.wav");

	//create actors
	neu::Scene scene;

	neu::Transform transform{ neu::Vector2{100,100} , 90 , {1,1} };

	std::unique_ptr<neu::Actor> actor = std::make_unique<neu::Actor>();
	std::unique_ptr<neu::PlayerComponent> pcomponent = std::make_unique<neu::PlayerComponent>();
	actor->AddComponent(std::move(pcomponent));
	std::unique_ptr<neu::SpriteComponent> scomponent = std::make_unique<neu::SpriteComponent>();
	scomponent->m_texture = texture;
	actor->AddComponent(std::move(scomponent));
	std::unique_ptr<neu::AudioComponent> acomponent = std::make_unique<neu::AudioComponent>();
	acomponent->Play();
	actor->AddComponent(std::move(acomponent));
	std::unique_ptr<neu::PhysicsComponent> phcomponent = std::make_unique<neu::PhysicsComponent>();
	actor->AddComponent(std::move(phcomponent));

	scene.Add(std::move(actor));

	float angle = 0;

	bool quit = false;

	while (!quit)
	{
		//update (engine)
		neu::g_time.Tick();
		neu::g_inputSystem.Update();
		//neu::g_audioSystems.Update;
		//neu::PlayerComponent::Update();

		if (g_inputSystem.GetKeyDown(key_escape)) quit = true;

		//angle += 90.0f * neu::g_time.deltaTime;//rotate

		scene.Update();

		//render
		neu::g_renderer.BeginFrame();//Begin Frame

		scene.Draw(neu::g_renderer);
		neu::g_renderer.Draw(texture, { 400, 300 }, angle, {2,2},{0.5f,0.5f});

		neu::g_renderer.EndFrame();//End Frame
	}

	//Shutdown
	//g_inputSystem.ShutDown;
	g_renderer.Shutdown();
	//g_audioSystem.Shutdown();
}