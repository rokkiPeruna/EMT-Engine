#include <EntityComponentSys/Components/Shapes/Triangle.hpp>

namespace jej
{

    Triangle::Triangle() :
        ShapeComponent(),
        m_points()
    {
        m_shapeType = ShapeType::Triangle;
    }

    Triangle::Triangle(const Vector2f p_points[3]) :
        ShapeComponent()
    {
        std::memcpy(&m_points, &p_points, 3u);
        m_shapeType = ShapeType::Triangle;
    }

    Triangle::~Triangle()
    {

    }

}