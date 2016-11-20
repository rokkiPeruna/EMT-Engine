#include <EntityComponentSys/Components/Shapes/Circle.hpp>

namespace jej
{

    Circle::Circle(Entity& entity) :
        ShapeComponent(entity),
        m_radius(1.f)
    {
        m_shapeType = ShapeType::Circle;
    }

    Circle::Circle(Entity& entity, const float radius) :
        ShapeComponent(entity),
        m_radius(radius)
    {
        m_shapeType = ShapeType::Circle;
    }

    Circle::~Circle()
    {

    }

}