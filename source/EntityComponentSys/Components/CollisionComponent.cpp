#include <EntityComponentSys/Components/CollisionComponent.hpp>
#include <EntityComponentSys/Systems/ShapeSystem.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>
#include <Utility/Math.hpp>

namespace jej
{
	CollisionComponent::CollisionComponent(Entity* p_entity) :
		Component(p_entity)
	{
		for (const auto& itr : ShapeSystem::GetInstance()._getComponentsRef<ShapeComponent>())
			if (itr->m_parentID == p_entity->GetID())
			{
				for (const auto& itr2 : itr.get()->m_shapes)
				m_AABB = Math::ConvexCollisionBox(&*itr2, p_entity->GetComponentPtr<TransformComponent>()->position);
				break;
			}


	}

	CollisionComponent::~CollisionComponent()
	{

	}



}