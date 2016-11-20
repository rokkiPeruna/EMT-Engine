#include <EntityComponentSys/Components/Shapes/Triangle.hpp>

namespace jej
{

    Triangle::Triangle(Entity& entity) :
        ShapeComponent(entity),
        m_points()
    {
        m_shapeType = ShapeType::Triangle;
    }

    Triangle::Triangle(Entity& entity, const Vector2f p_points[3]) :
        ShapeComponent(entity)
    {
        std::memcpy(&m_points, &p_points, 3u);
        m_shapeType = ShapeType::Triangle;
    }

    Triangle::~Triangle()
    {

    }

}