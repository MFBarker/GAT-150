#include "MyGame.h"
#include "Engine.h"
#include "GameComponents/EnemyComponent.h"

void MyGame::Initialize()
{
	REGISTER_CLASS(EnemyComponent);

	neu::g_audioSystem.AddAudio("background", "Audio/music.mp3");

	neu::g_audioSystem.AddAudio("coin", "Audio/coin.wav");
	neu::g_audioSystem.AddAudio("hit", "Audio/hit.wav");

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

	g_audioSystem.PlayAudio("background", 1.0f, 1.0f, true);

	std::cout << "HINT: Press ENTER to Start \n";

	neu::g_eventManager.Subscribe("EVENT_ADD_POINTS", std::bind(&MyGame::OnNotify, this, std::placeholders::_1));
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
	{
		m_scene->GetActorFromName("Title")->SetActive(true);

		if (g_inputSystem.GetKeyDown(neu::key_enter) == neu::InputSystem::Pressed)
		{
			m_scene->GetActorFromName("Title")->SetActive(false);
			m_scene->GetActorFromName("Score")->SetActive(true);
			m_scene->GetActorFromName("Health")->SetActive(true);
			m_gameState = gameState::Level_Start;
		}
	}
		break;

	case gameState::Level_Start:
	{
		auto actor = neu::Factory::Instance().Create<Actor>("Player");
		actor->m_transform.position = { neu::randomf(0,800),100.0f };
		actor->Initialize();

		m_scene->Add(std::move(actor));

		for (int i = 0; i < 10; i++)
		{
			auto actor = neu::Factory::Instance().Create<Actor>("Coin");
			actor->m_transform.position = { neu::randomf(0,800),100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		for (int i = 0; i < 3; i++)
		{
			auto actor = neu::Factory::Instance().Create<Actor>("Ghost");
			actor->m_transform.position = { neu::randomf(0,800),100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}

		m_gameState = gameState::Game;
	}
		break;

	case gameState::Game:
	{
		auto actor = m_scene->GetActorFromName("Score");
		auto component = actor->GetComponent<neu::TextComponent>();
		component->SetText(std::to_string(m_score));
		if (g_inputSystem.GetKeyDown(key_death) == neu::InputSystem::Pressed)
		{
			m_gameState = gameState::Game_Over;
		}
	}
		break;
	case gameState::Player_Dead:
		m_stateTimer -= neu::g_time.deltaTime;
		if (m_stateTimer = 0)
		{
			m_gameState = (m_lives > 0) ? gameState::Level_Start : gameState::Game_Over;
		}
		break;

	case gameState::Game_Over:
		m_scene->GetActorFromName("Score")->SetActive(false);
		m_scene->GetActorFromName("Health")->SetActive(false);
		m_scene->GetActorFromName("GameOver")->SetActive(true);

		if (g_inputSystem.GetKeyDown(neu::key_enter) == neu::InputSystem::Pressed)
		{
			m_scene->GetActorFromName("GameOver")->SetActive(false);
			m_gameState = gameState::Title_Screen;
		}
	
		break;
	}

	m_scene->Update();
}

void MyGame::Draw(neu::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void MyGame::OnNotify(const neu::Event& event)
{
	if (event.name == "EVENT_ADD_POINTS")
	{
		std::cout << event.name << std::endl;
		std::cout << std::get<int>(event.data) << std::endl;
		m_score += std::get<int>(event.data);
	}
	if (event.name == "EVENT_PLAYER_DEAD")
	{
		m_gameState = gameState::Player_Dead;
		m_stateTimer = 3;
	}
}
