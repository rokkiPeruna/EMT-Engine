#include <EntityComponentSys/Components/CollisionComponent.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>

namespace jej
{
	CollisionComponent::CollisionComponent(Entity* p_entity) :
		Component(p_entity),
		IsColliding(false)
	{

	}

	CollisionComponent::~CollisionComponent()
	{

	}



}