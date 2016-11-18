#include <EntityComponentSys\Components\Shapes\Rectangle.hpp>

namespace jej
{

	Rectangle::Rectangle() :
		ShapeComponent(),
		m_extents(1.f, 1.f)
	{
		m_shapeType = ShapeType::Rectangle;
	}

	Rectangle::Rectangle(const Vector2f extents) :
		ShapeComponent(),
		m_extents(extents)
	{
		m_shapeType = ShapeType::Rectangle;
	}

	Rectangle::~Rectangle()
	{

	}

}