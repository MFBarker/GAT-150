#include "Model.h"
#include "../Core/File.h"
#include <sstream>

neu::Model::Model(const std::string& filename)
{
	Load(filename);
	m_radius = CalculateRadius();
}

void neu::Model::Draw(neu::Renderer& renderer, const neu::Vector2& position, float angle, const Vector2& scale)
{
	for (int i = 0; i < m_points.size() - 1; i++)
	{
		Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
		Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;
		renderer.DrawLine(p1, p2, m_color);
	}
}

 void neu::Model::Load(std::string filename)
 {
	 std::string buffer;

	 neu::ReadFile(filename, buffer);

	 //read color
	 std::istringstream sColor(buffer);
	 sColor >> m_color;

	 std::istringstream stream(buffer);
	 std::string line;
	 std::getline(stream, line);

	 size_t numPoints = std::stoi(line);

	 for (size_t i = 0; i < numPoints;)
	 {
		 Vector2 point;
		 m_points.push_back(point);
	 }

 }

 float neu::Model::CalculateRadius()
 {
	 float radius = 0;

	 for (auto point : m_points)
	 {
		 //
	 }

	 return radius;
 }

