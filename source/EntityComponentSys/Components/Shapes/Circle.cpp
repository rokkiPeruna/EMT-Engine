#include <EntityComponentSys/Components/Shapes/Circle.hpp>

namespace jej
{

	Circle::Circle():
		ShapeComponent(),
		m_radius(1.f)
	{
		m_shapeType = ShapeType::Circle;
	}

	Circle::Circle(const float radius):
		ShapeComponent(),
		m_radius(radius)
	{
		m_shapeType = ShapeType::Circle;
	}

	Circle::~Circle()
	{

	}

}