#include <EntityComponentSys/Components/Shapes/Rectangle.hpp>

namespace jej
{

    Rectangle::Rectangle(Entity& entity) :
        ShapeComponent(entity),
        m_extents(1.f, 1.f)
    {
        m_shapeType = ShapeType::Rectangle;
    }

    Rectangle::Rectangle(Entity& entity, const Vector2f extents) :
        ShapeComponent(entity),
        m_extents(extents)
    {
        m_shapeType = ShapeType::Rectangle;
    }

    Rectangle::~Rectangle()
    {

    }

}