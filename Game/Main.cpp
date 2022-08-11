#include "Engine.h"

int main()
{
	//Initialize memory
	InitializeMemory();
	g_renderer.Initialize();
	g_inputSystem.Initialize();
	g_audioSystem.Initialize();
	g_resources.Initialize();

	neu::SetFilePath("../Assets");

	g_renderer.CreateWindow("Neumont", 800, 600);
	g_renderer.SetClearColor(neu::Color{0,0,0,255});

	//create Texture
	/*std::shared_ptr<neu::Texture> texture = std::make_shared<neu::Texture>();
	texture->Create(neu::g_renderer, "Sprites/SpaceShip.png");*/

	std::shared_ptr<neu::Texture> texture = neu::g_resources.Get("Sprites/Spaceship", &neu::g_renderer);

	/*std::shared_ptr<neu::Model> model = std::make_shared<neu::Model>();
	model->Create("Models/Player.txt");*/

	std::shared_ptr<neu::Model> model = neu::g_resources.Get<neu::Model>("Models/Player.txt");
	std::shared_ptr<neu::Model> model2 = neu::g_resources.Get<neu::Model>("Models/Player.txt");

	neu::g_audioSystem.AddAudio("temp", "Audio/temp.wav");

	//create actors
	neu::Scene scene;

	neu::Transform transform{ neu::Vector2{100,100} , 90 , {3,3} };

	std::unique_ptr<neu::Actor> actor = std::make_unique<neu::Actor>();
	std::unique_ptr<neu::PlayerComponent> pcomponent = std::make_unique<neu::PlayerComponent>();
	actor->AddComponent(std::move(pcomponent));

	std::unique_ptr<neu::ModelComponent> mcomponent = std::make_unique<neu::ModelComponent>();
	mcomponent->m_model = model;
	actor->AddComponent(std::move(mcomponent));

	/*std::unique_ptr<neu::SpriteComponent> scomponent = std::make_unique<neu::SpriteComponent>();
	scomponent->m_texture = texture;
	actor->AddComponent(std::move(scomponent));*/

	std::unique_ptr<neu::AudioComponent> acomponent = std::make_unique<neu::AudioComponent>();
	acomponent->m_soundName = "temp";
	actor->AddComponent(std::move(acomponent));

	std::unique_ptr<neu::PhysicsComponent> phcomponent = std::make_unique<neu::PhysicsComponent>();
	actor->AddComponent(std::move(phcomponent));

	neu::Transform transformC { neu::Vector2{40,30} , 90 , {1,1} };
	std::unique_ptr<neu::Actor> child = std::make_unique<neu::Actor>(transformC);

	std::unique_ptr<neu::ModelComponent> mcomponentC = std::make_unique<neu::ModelComponent>();
	mcomponentC->m_model = model;
	child->AddComponent(std::move(mcomponentC));
	actor->AddChild(std::move(child));

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