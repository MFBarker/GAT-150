#include "PlayerComponents.h"
#include "Engine.h"
#include <iostream>

namespace neu
{
	void PlayerComponent::Initialize()
	{
		CharacterComponent::Initialize();

		g_eventManager.Subscribe("EVENT_PICKUP", std::bind(&CharacterComponent::OnNotify, this, std::placeholders::_1), m_owner);
		g_eventManager.Subscribe("EVENT_HEALTH", std::bind(&CharacterComponent::OnNotify, this, std::placeholders::_1), m_owner);
	}

	void PlayerComponent::Update()
	{
		float thrust = 0;

		// update transform with input
		Vector2 direction = Vector2::zero;
		if (g_inputSystem.GetKeyDown(key_left) == (InputSystem::State::Held || InputSystem::State::Pressed))
		{
			direction = Vector2::left;
		}
		if (g_inputSystem.GetKeyDown(key_right) == (InputSystem::State::Held || InputSystem::State::Pressed))
		{
			direction = Vector2::right;
		}

		if (g_inputSystem.GetKeyDown(key_up) == (InputSystem::State::Held || InputSystem::State::Pressed))
		{
			thrust = speed;
		}
		if (g_inputSystem.GetKeyDown(key_down) == (InputSystem::State::Held || InputSystem::State::Pressed))
		{
			direction = Vector2::down;
		}

		Vector2 velocity;
		auto acomponent = m_owner->GetComponent<PhysicsComponent>();
		if (acomponent)
		{
			acomponent->ApplyForce(direction * speed);
			velocity = acomponent->velocity;
		}


		//m_owner->m_transform.position += direction * 300 * g_time.deltaTime;

		//jump
		if (g_inputSystem.GetKeyDown(key_space) == InputSystem::State::Pressed)
		{
			auto acomponent = m_owner->GetComponent<PhysicsComponent>();
			if (acomponent)
			{
				acomponent->ApplyForce(Vector2::up * speed);

			}
		}

		auto renderComponent = m_owner->GetComponent<RenderComponent>();
		if (renderComponent)
		{
			if (velocity.x != 0) renderComponent->SetFlipHorizontal(velocity.x < 0);
		}
	}

	void PlayerComponent::OnNotify(const Event& event)
	{
		if (event.name == "EVENT_DAMAGE")
		{
			health -= std::get<float>(event.data);
			if (health <= 0)
			{
				m_owner->SetDestroy();

				Event event;
				event.name = "EVENT_PLAYER_DEAD";

				g_eventManager.Notify(event);
			}
		}
		if (event.name == "EVENT_HEALTH")
		{
			health += std::get<float>(event.data);
		}
	}

	void PlayerComponent::OnCollisionEnter(Actor* other) 
	{
		if (other->GetName() == "Coin")
		{
			Event event;
			event.name = "EVENT_ADD_POINTS";
			event.data = 100;

			g_eventManager.Notify(event);
			other->SetDestroy();
		}

		if (other->GetName() == "Enemy")
		{
			Event event;
			event.name = "EVENT_DAMAGE";
			event.data = damage;
			event.reciever = other;

			neu::g_eventManager.Notify(event);
		}

		std::cout << "player enter \n";
	}
	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		std::cout << "player exit \n";
	}

	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		CharacterComponent::Read(value);

		std::string player_name;
		READ_DATA(value,player_name);
		READ_DATA(value,jump);

		return true;
	}
	
}

