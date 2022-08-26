#include "MyGame.h"
#include "Engine.h"

void MyGame::Initialize()
{
	m_scene = std::make_unique<neu::Scene>();

	rapidjson::Document document;
	std::vector<std::string> sceneNames = { "Scenes/level.txt", "Scenes/tilemap.txt", "Scenes/prefabs.txt"};

	for (auto sceneName : sceneNames)
	{
		bool success = neu::json::Load(sceneName, document);

		if (!success) 
		{
			LOG("Could Not Load Scene %s", sceneName.c_str());
			continue;
		}

		m_scene->Read(document);
	}

	m_scene->Initialize();

	for (int i = 0; i < 10; i++)
	{
		auto actor = neu::Factory::Instance().Create<Actor>("Coin");
		actor->m_transform.position = { neu::randomf(0,800),100.0f };
		actor->Initialize();

		m_scene->Add(std::move(actor));
	}
}

void MyGame::Shutdown()
{
	m_scene->RemoveAll();
}

void MyGame::Update()
{
	m_scene->Update();
}

void MyGame::Draw(neu::Renderer& renderer)
{
	m_scene->Draw(renderer);
}
