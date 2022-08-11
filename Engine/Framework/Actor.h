#pragma once
#include "GameObject.h"
#include "Component.h"
#include <vector>
#include <memory>

namespace neu
{
	class Scene;
	class Renderer;

	class Actor : public GameObject
	{
	public:
		Actor() = default;
		Actor(const Transform& transform) : m_transform{ transform } {}
		
		virtual void Update() override;
		virtual void Draw(neu::Renderer& renderer);

		void AddChild(std::unique_ptr<Actor> child);

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		virtual void OnCollision(Actor* other) {}
		float GetRadius() { return 0; }//m_model.GetRadius()* std::max(m_transform.scale.x, m_transform.scale.y);}
	
		std::string& GetTag() { return m_tag; }

		friend class Scene;

		neu::Transform m_transform;
	protected:
		std::string m_tag;
		bool m_destroy = false;

		//Physiscs
		Vector2 m_velocity;
		float m_damping = 1;
		
		Scene* m_scene = nullptr;
		Actor* m_parent = nullptr;
		
		std::vector<std::unique_ptr<Component>> m_component;
		std::vector<std::unique_ptr<Actor>> m_children;

	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_component)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;

		}

		return nullptr;
	}

}