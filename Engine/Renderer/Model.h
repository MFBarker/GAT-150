#pragma once
#include "Renderer.h"
#include <vector>
#include <string>

namespace neu
{
	class Model
	{
	public:
		Model() = default;
		Model(const std::vector<neu::Vector2>& points, const neu::Color& color)
		{
			m_points = points;
			m_color = color;
		}

		Model(const std::string& filename);

		void Draw(neu::Renderer& renderer, const neu::Vector2& position, float angle, const Vector2& scale= Vector2 { 1,1 });
	
		void Load(std::string filename);

		float CalculateRadius();

		float GetRadius() { return m_radius; }
	
	private:
		neu::Color m_color;
		std::vector<neu::Vector2> m_points;

		float m_radius = 0;
	};
}