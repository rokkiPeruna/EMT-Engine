#include <EntityComponentSys/Components/Shapes/Rectangle.hpp>

namespace jej
{

    Rectangle::Rectangle() :
        Shape()
    {
        m_shapeType = ShapeType::Rectangle;

		_load(3.f, 2.f);
    }

	Rectangle::Rectangle(const float x, const float y) :
        Shape()
    {
        m_shapeType = ShapeType::Rectangle;

		_load(x, y);
    }

    Rectangle::~Rectangle()
    {

    }

	void Rectangle::_load(const float x, const float y)
	{
		m_points.reserve(4);

		m_points.emplace_back(x, y);
		m_points.emplace_back(-x, y);
		m_points.emplace_back(-x, -y);
		m_points.emplace_back(x, -y);
	}

    void Rectangle::_update(const float p_deltaTime)
    {

    }
}