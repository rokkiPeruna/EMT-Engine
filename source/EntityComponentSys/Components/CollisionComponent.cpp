#include <EntityComponentSys/Components/CollisionComponent.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>

namespace jej
{
	CollisionComponent::CollisionComponent(Entity* p_entity, TransformComponent* p_transformComponent) :
		Component(p_entity),
		m_position_min(),
		m_position_max()
	{
		


	}

	CollisionComponent::~CollisionComponent()
	{

	}


}