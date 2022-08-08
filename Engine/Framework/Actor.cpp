#include "Actor.h"
#include "Components/RenderComponent.h"

namespace neu
{
	void Actor::Update()
	{
		for (auto& component : m_component)
		{
			component->Update();
		}
	}

	void Actor::Draw(neu::Renderer& renderer)
	{
		for (auto& component : m_component)
		{
			auto renderComponent = dynamic_cast<RenderComponent*>(component.get());

			if (renderComponent)
			{
				renderComponent->Draw(renderer);
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_component.push_back(std::move(component));
	}

}

