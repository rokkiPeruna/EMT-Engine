#include <EntityComponentSys/Components/Shapes/Convex.hpp>

namespace jej
{

    Convex::Convex(Entity& entity) :
        ShapeComponent(entity)
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

	Convex::Convex(Entity& entity, const std::vector<float>& p_points) :
        ShapeComponent(entity)
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

	bool Convex::Transform(const std::vector<float>& p_newPoints)
	{
		if (m_points.size() != p_newPoints.size() * 0.5f)
			return false;

		for (unsigned int i = 0; i < m_points.size(); ++i)
			m_points[i] = { p_newPoints[i + 1 * i], p_newPoints[(i + 1) + 1 * i] };

		return true;
	}
}