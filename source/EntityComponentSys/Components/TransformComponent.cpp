#include <EntityComponentSys/Components/TransformComponent.hpp>



namespace jej
{
    TransformComponent::TransformComponent():
        Component()
    {
        //Give component it's right enum type
        m_componentType = ComponentType::Transform;
    }
    //

    TransformComponent::TransformComponent(const Vector2f& p_position, const Vector2f& p_scale, const Vector4f& p_rotation):
        Component(),
        position(p_position),
        scale(p_scale),
        rotation(p_rotation)
    {
        m_componentType = ComponentType::Transform;
    }

    TransformComponent::~TransformComponent()
    {
        
    }
    //
}