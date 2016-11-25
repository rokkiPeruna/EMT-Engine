#include <EntityComponentSys/Components/Shapes/Convex.hpp>

namespace jej
{

    Convex::Convex() :
        Shape()
    {
        std::vector<float> points =
        {
            3.f, 1.f,
            1.f, 3.f,
            -1.f, 1.f,
            -1.f, -2.f,
            2.f, -2.f
        };
        
        m_shapeType = ShapeType::Convex;

		_load(points);
    }

	Convex::Convex(const std::vector<float>& p_points) :
        Shape()
    {
        m_shapeType = ShapeType::Convex;
     
		_load(p_points);
    }

    Convex::~Convex()
    {

    }

	void Convex::_load(const std::vector<float>& p_points)
	{
		if (p_points.size() % 2)
			return;

		m_points.reserve(p_points.size() * 0.5f);

		for (unsigned int i = 0u; i < p_points.size() * 0.5f; ++i)
			m_points.emplace_back(p_points[i + 1 * i], p_points[(i + 1) + 1 * i]);
	}

    void Convex::_update(const float p_deltaTime)
    {

    }
}