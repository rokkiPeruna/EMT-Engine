#include <EntityComponentSys/Components/Shapes/Convex.hpp>

namespace jej
{

    Convex::Convex() :
        ShapeComponent(),
        m_pointCount(5u)
    {
        Vector2f points[5u] =
        {
            Vector2f(3.f, 1.f),
            Vector2f(1.f, 3.f),
            Vector2f(-1.f, 1.f),
            Vector2f(-1.f, -2.f),
            Vector2f(2.f, -2.f)
        };
        std::memcpy(&m_points, &points, m_pointCount);
        m_shapeType = ShapeType::Convex;
    }

    Convex::Convex(const unsigned int p_pointCount, Vector2f*p_points) :
        ShapeComponent(),
        m_pointCount(p_pointCount)
    {
        m_shapeType = ShapeType::Convex;
        std::memcpy(&m_points, &p_points, m_pointCount);
    }

    Convex::~Convex()
    {

    }

}