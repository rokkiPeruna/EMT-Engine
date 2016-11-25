#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{

    ShapeComponent::ShapeComponent(Entity& entity, Vector4i p_color) :
        Component(entity),
        ColorRGBA(p_color),
        m_shapes()
    {
        m_componentType = ComponentType::Shape;
    }


    ShapeComponent::~ShapeComponent()
    {

    }


}