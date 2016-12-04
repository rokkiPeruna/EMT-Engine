#include <EntityComponentSys/Components/TransformComponent.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>



namespace jej
{
    TransformComponent::TransformComponent(Entity* entity, const Vector2f& p_position, const  Vector2f& p_scale, const Vector4f& p_rotation) :
        Component(entity),
        position(p_position),
        scale(p_scale),
        rotation(p_rotation)
    {
        //Give component it's right enum type
        m_componentType = ComponentType::Transform;
    }
    //

    TransformComponent::TransformComponent(Entity* entity, const TransformComponent& p_toCopy) :
        Component(entity),
        position(p_toCopy.position),
        scale(p_toCopy.scale),
        rotation(p_toCopy.rotation)
    {
        m_componentType = ComponentType::Transform;
    }

    TransformComponent::~TransformComponent()
    {

    }
    //
}