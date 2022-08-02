#include "Actor.h"

void neu::Actor::Draw(neu::Renderer& renderer)
{
	m_model.Draw(renderer, m_transform.position, m_transform.rotation, m_transform.scale);
}
