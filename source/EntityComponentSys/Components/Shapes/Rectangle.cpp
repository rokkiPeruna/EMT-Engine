#include <EntityComponentSys/Components/Shapes/Rectangle.hpp>

namespace jej
{

    Rectangle::Rectangle(Entity& entity) :
        ShapeComponent(entity)
    {
        m_shapeType = ShapeType::Rectangle;

		_load(3.f, 2.f);
    }

	Rectangle::Rectangle(Entity& entity, const float x, const float y) :
        ShapeComponent(entity)
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

	bool Rectangle::Transform(const std::vector<float>& p_newPoints)
	{
		if (m_points.size() != p_newPoints.size() * 0.5f)
			return false;

		for (unsigned int i = 0; i < m_points.size(); ++i)
			m_points[i] = { p_newPoints[i + 1 * i], p_newPoints[(i + 1) + 1 * i] };

		return true;
	}

}