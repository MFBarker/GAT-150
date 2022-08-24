#pragma once
#include "GameObject.h"
#include "Serialization/Serialization.h"
#include "Component.h"
#include <vector>
#include <memory>

namespace neu
{
	class Scene;
	class Renderer;

	class Actor : public GameObject, public ISerializable
	{
	public:

		Actor() = default;
		Actor(const Transform& transform) : m_transform{ transform } {}
		
		void Initialize() override;
		virtual void Update() override;
		virtual void Draw(neu::Renderer& renderer);

		void AddChild(std::unique_ptr<Actor> child);

		void AddComponent(std::unique_ptr<Component> component);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		template<typename T>
		T* GetComponent();

		virtual void OnCollision(Actor* other) {}
		float GetRadius() { return 0; }//m_model.GetRadius()* std::max(m_transform.scale.x, m_transform.scale.y);}
	
		std::string& GetTag() { return tag; }
		std::string& SetTag(const std::string& tag) { this->tag = tag; }

		std::string& GetName() { return name; }
		std::string& SetName(const std::string& name) { this->name = name; }

		void SetDestroy() { m_destroy = true; }

		friend class Scene;

		neu::Transform m_transform = Transform(0,0,{1,1});
	protected:
		std::string name;
		std::string tag;


		bool m_destroy = false;

		//Physiscs
		Vector2 velocity;
		float damping = 1;
		
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