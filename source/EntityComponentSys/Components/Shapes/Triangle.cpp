#include <EntityComponentSys/Components/Shapes/Triangle.hpp>

namespace jej
{

	Triangle::Triangle() :
		Shape()
	{
		m_shapeType = ShapeType::Triangle;

		_load({0.f, 2.f, -2.f, -1.f, 2.f, -1.f});
	}

	Triangle::Triangle(const float(&p_points)[6]) :
        Shape()
	{
		m_shapeType = ShapeType::Triangle;

		_load(p_points);
	}

	Triangle::~Triangle()
	{

	}

	void Triangle::_load(const float(&p_points)[6])
	{
		m_points.reserve(3);

		for (char i = 0; i < 3; ++i)
			m_points.emplace_back(p_points[i + 1 * i], p_points[(i + 1) + 1 * i]);
	}

    void Triangle::_update(const float p_deltaTime)
    {

    }
}