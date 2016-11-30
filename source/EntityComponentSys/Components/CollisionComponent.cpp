#include <EntityComponentSys/Components/CollisionComponent.hpp>
#include <Utility/Math.hpp>

namespace jej
{
	CollisionComponent::CollisionComponent(Entity* p_entity, const Shape* p_shape) :
		Component(p_entity)
	{
		m_min = Math::ConvexCollisionBox(p_shape).first;
		m_max = Math::ConvexCollisionBox(p_shape).second;
	}

	CollisionComponent::~CollisionComponent()
	{

	}


}