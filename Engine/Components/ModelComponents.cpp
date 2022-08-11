#include "ModelComponents.h"
#include "Renderer/Model.h"
#include "Framework/Actor.h"

void neu::ModelComponent::Update()
{
	//
}

void neu::ModelComponent::Draw(Renderer& renderer)
{
	m_model->Draw(renderer, m_owner->m_transform);
}
