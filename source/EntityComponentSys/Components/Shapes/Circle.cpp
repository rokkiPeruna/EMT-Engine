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

    void Circle::_update(const float p_deltaTime)
    {

    }

}