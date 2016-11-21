#include <EntityComponentSys/Components/Shapes/Circle.hpp>

#include <math.h>

namespace jej
{

    Circle::Circle() :
        Shape()
    {
        m_shapeType = ShapeType::Circle;

		_load(2.f, 15u);
    }

    Circle::Circle(const float radius, const unsigned int accuracy) :
        Shape()
    {
        m_shapeType = ShapeType::Circle;

		_load(radius, accuracy);
    }

    Circle::~Circle()
    {

    }

	void Circle::_load(const float radius, const unsigned int accuracy)
	{
		const unsigned int pointCount = accuracy > 3u ? accuracy : 3u;
		const float radians = (8 * atan(1)) / pointCount;

		m_points.reserve(pointCount + 1);
		float theta = 0.f;

		for (unsigned int i = 0u; i < pointCount; ++i)
		{
			m_points.emplace_back(
				((cos(theta) * radius) / radius + 1.f) * 0.5f,
				1.f - ((sin(theta) * radius) / radius + 1.f) * 0.5f
				);

			theta += radians;
		}
	}

	/*bool Circle::Transform(const std::vector<float>& p_newPoints)
	{
		if (m_points.size() != p_newPoints.size() * 0.5f)
			return false;

		for (unsigned int i = 0; i < m_points.size(); ++i)
			m_points[i] = { p_newPoints[i + 1 * i], p_newPoints[(i + 1) + 1 * i] };

		return true;
	}*/

}