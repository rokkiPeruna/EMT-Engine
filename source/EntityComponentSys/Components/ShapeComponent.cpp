#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{

    ShapeComponent::ShapeComponent(Entity& entity) :
        Component(entity),
		m_points()
    {
        m_componentType = ComponentType::Shape;
    }

    ShapeComponent::~ShapeComponent()
    {

    }

}