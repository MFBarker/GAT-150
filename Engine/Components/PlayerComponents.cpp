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
		if (g_inputSystem.GetKeyDown(key_left) && (InputSystem::State::Held || InputSystem::State::Pressed))
		{
			direction = Vector2::left;
		}
		if (g_inputSystem.GetKeyDown(key_right) && (InputSystem::State::Held || InputSystem::State::Pressed))
		{
			direction = Vector2::right;
		}

		if (g_inputSystem.GetKeyDown(key_up) && (InputSystem::State::Held || InputSystem::State::Pressed))
		{
			thrust = speed;
		}
		if (g_inputSystem.GetKeyDown(key_down) && (InputSystem::State::Held || InputSystem::State::Pressed))
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

		// set camera 
		auto camera = m_owner->GetScene()->GetActorFromName("Camera");
		if (camera)
		{
			camera->m_transform.position = math::Lerp(camera -> m_transform.position, m_owner->m_transform.position, 2 * g_time.deltaTime);
		}

		//jump
		if (m_groundCount > 0 && g_inputSystem.GetKeyDown(key_space) == InputSystem::State::Pressed)
		{
			Vector2 velocity;
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				// if in the air (m_groundCount == 0) then reduce force 
				float multiplier = (m_groundCount > 0) ? 1 : 0.2f;

				component->ApplyForce(direction * speed * multiplier);
				velocity = component->velocity;
			}
		}

		auto animComponent = m_owner->GetComponent<SprAnimComponent>();
		if (animComponent)
		{
			if (velocity.x != 0) animComponent->SetFlipHorizontal(velocity.x < 0);
			if (std::fabs(velocity.x) > 0)
			{
				animComponent->SetSequence("run");
			}
			else
			{
				animComponent->SetSequence("idle");
			}
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
		if (other->GetTag() == "Ground")
		{
			m_groundCount++;
		}

		if (other->GetName() == "Coin")
		{
			Event event;
			event.name = "EVENT_ADD_POINTS";
			event.data = 100;

			g_audioSystem.PlayAudio("coin");

			g_eventManager.Notify(event);
			other->SetDestroy();
		}

		if (other->GetName() == "Enemy")
		{
			Event event;
			event.name = "EVENT_DAMAGE";
			event.data = damage;
			event.reciever = other;

			g_audioSystem.PlayAudio("hit");

			neu::g_eventManager.Notify(event);
		}

		//std::cout << "player enter \n";
	}
	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		if (other->GetTag() == "Ground")
		{
			m_groundCount--;
		}

		//std::cout << "player exit \n";
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

