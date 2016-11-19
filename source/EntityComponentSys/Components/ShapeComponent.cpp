#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{

	ShapeComponent::ShapeComponent():
        Component()
	{
        m_componentType = ComponentType::Shape;
	}

	ShapeComponent::~ShapeComponent()
	{

	}

}