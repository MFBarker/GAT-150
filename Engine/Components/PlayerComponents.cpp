#include "PlayerComponents.h"
#include "Engine.h"
#include <iostream>

namespace neu
{
	void PlayerComponent::Update()
	{
		float thrust = 0;

		// update transform with input
		Vector2 direction = Vector2::zero;
		if (g_inputSystem.GetKeyDown(key_left) == InputSystem::State::Held)
		{
			direction = Vector2::left;
		}
		if (g_inputSystem.GetKeyDown(key_right) == InputSystem::State::Held)
		{
			direction = Vector2::right;
		}

		if (g_inputSystem.GetKeyDown(key_up) == InputSystem::State::Held)
		{
			thrust = speed;
		}
		if (g_inputSystem.GetKeyDown(key_down) == InputSystem::State::Held)
		{
			direction = Vector2::down;
		}

		auto acomponent = m_owner->GetComponent<PhysicsComponent>();
		if (acomponent)
		{
			//Vector2 force = Vector2::Rotate( { 1, 0 },math::DegToRad(m_owner->m_transform.rotation))* thrust;
			acomponent->ApplyForce(direction * speed);

			//force = (Vector2{400,300} - m_owner->m_transform.position).Normalized() * 60.0f;
			//acomponent->ApplyForce(force);
		}


		//m_owner->m_transform.position += direction * 300 * g_time.deltaTime;

		//jump
		if (g_inputSystem.GetKeyDown(key_space) == InputSystem::State::Pressed)
		{
			auto acomponent = m_owner->GetComponent<PhysicsComponent>();
			if (acomponent)
			{
				//Vector2 force = Vector2::Rotate( { 1, 0 },math::DegToRad(m_owner->m_transform.rotation))* thrust;
				acomponent->ApplyForce(Vector2::up * speed);

				//force = (Vector2{400,300} - m_owner->m_transform.position).Normalized() * 60.0f;
			}
		}

		//Wrap
		/*if (m_owner->m_transform.position.x > neu::g_renderer.GetWidth()) m_owner->m_transform.position.x = 0;
		if (m_owner->m_transform.position.x > 0) m_owner->m_transform.position.x = (float)neu::g_renderer.GetWidth();
		if (m_owner->m_transform.position.y > neu::g_renderer.GetHeight()) m_owner->m_transform.position.y = 0;
		if (m_owner->m_transform.position.y > 0) m_owner->m_transform.position.y = (float)neu::g_renderer.GetHeight();
		*/
		
	}

	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		std::string player_name;
		READ_DATA(value,player_name);
		READ_DATA(value,speed);

		return true;
	}
}

