#include <EntityComponentSys/Components/CollisionComponent.hpp>
#include <EntityComponentSys/Systems/ShapeSystem.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>
#include <Utility/Math.hpp>

namespace jej
{
    CollisionComponent::CollisionComponent(Entity* p_entity) :
        Component(p_entity),
        m_min(),
        m_max()
    {
        for (const auto& itr : ShapeSystem::GetInstance()._getComponentsRef<ShapeComponent>())
            if (itr->m_parentID == p_entity->GetID())
            {
                // TODO: work work work..
                //				m_min = Math::ConvexCollisionBox(itr->m_shapes.at);
                //			m_max = Math::ConvexCollisionBox(p_shape).second;
                break;
            }


    }

    CollisionComponent::~CollisionComponent()
    {

    }



}