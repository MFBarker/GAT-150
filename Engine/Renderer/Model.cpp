#include "Model.h"
#include "Core/File.h"
#include "Core/Logger.h"
#include "Math/Transform.h"
#include <sstream>

neu::Model::Model(const std::string& filename)
{
	Load(filename);
	m_radius = CalculateRadius();
}

bool neu::Model::Create(const std::string filename)
{
	if (!Load(filename))
	{
		LOG("ERROR: Could Not Create Model %s", filename.c_str());
		return false;
	}
	return true;
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

void neu::Model::Draw(neu::Renderer& renderer, const Transform& transform)
{
	Matrix3x3 mx = transform.matrix;

	//if (m_points.size() == 0) return;

	for (int i = 0; i < m_points.size() - 1; i++)
	{
		Vector2 p1 = mx * m_points[i];
		Vector2 p2 = mx * m_points[i + 1];
		renderer.DrawLine(p1, p2, m_color);
	}
}

 bool neu::Model::Load(const std::string filename)
 {
	 std::string buffer;

	 if (!neu::ReadFile(filename, buffer))
	 {
		 LOG("ERROR: Could Not Read File %s", filename.c_str());
		 return false;
	 }

	 //read color
	 std::istringstream stream(buffer);
	 stream >> m_color;

	 std::string line;
	 std::getline(stream, line);

	 size_t numPoints = std::stoi(line);

	 for (size_t i = 0; i < numPoints; i++)
	 {
		 Vector2 point;
		 stream >> point;

		 m_points.push_back(point);
	 }
	 return true;
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

