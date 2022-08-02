#pragma once
#include "GameObject.h"
#include "../Renderer/Model.h"

namespace neu
{
	class Scene;

	class Actor : public GameObject
	{
	public:
		Actor() = default;
		Actor(const Model model, const Transform transform) : GameObject{ transform }, m_model{model}  {}

		virtual void Update() override {}
		virtual void Draw(neu::Renderer& renderer);

		virtual void OnCollision(Actor* other) {}
		float GetRadius() { return m_model.GetRadius() * m_transform.scale; }
		std::string& GetTag() { return m_tag; }

		friend class Scene;

	public:

	protected:
		std::string m_tag;

		bool m_destroy = false;

		Vector2 m_velocity;
		float m_damping = 1;

		Scene* m_scene = nullptr;
		Model m_model;
		
	};
}