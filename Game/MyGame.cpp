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

	m_gameState = gameState::Title_Screen;

	neu::g_eventManager.Subscribe("EVENT_ADD_POINTS", std::bind(&MyGame::OnAddPoints, this, std::placeholders::_1));
}

void MyGame::Shutdown()
{
	m_scene->RemoveAll();
}

void MyGame::Update()
{
	switch (m_gameState) 
	{
	case gameState::Title_Screen:
		if (g_inputSystem.GetKeyDown(neu::key_enter) == neu::InputSystem::Pressed)
		{
			//m_scene->GetActorFromName("Title")->SetActive(false);
			m_gameState = gameState::Level_Start;
		}
		break;

	case gameState::Level_Start:
		for (int i = 0; i < 10; i++)
		{
			auto actor = neu::Factory::Instance().Create<Actor>("Coin");
			actor->m_transform.position = { neu::randomf(0,800),100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		m_gameState = gameState::Game;
		break;

	case gameState::Game:
		g_inputSystem.Update();
		break;
	case gameState::Player_Dead:
		m_stateTimer -= neu::g_time.deltaTime;
		if (m_stateTimer = 0)
		{
			m_gameState = (m_lives > 0) ? gameState::Level_Start : gameState::Game_Over;
		}
		break;

	case gameState::Game_Over:
		//GameOver Title Active
		break;
	}

	m_scene->Update();
}

void MyGame::Draw(neu::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void MyGame::OnAddPoints(const neu::Event& event)
{
	std::cout << event.name << std::endl;
	std::cout << std::get<int>(event.data) << std::endl;
}

void MyGame::OnPlayerDead(const neu::Event& event)
{
	m_gameState = gameState::Player_Dead;
	m_stateTimer = 3;
}
