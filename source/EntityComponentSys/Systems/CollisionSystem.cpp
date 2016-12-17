#include <EntityComponentSys/Systems/ShapeSystem.hpp>
#include <EntityComponentSys/Systems/CollisionSystem.hpp>
#include <EntityComponentSys/Components/ShapeComponent.hpp>
#include <Utility/Math.hpp>
#include <Utility/Messenger.hpp>
#include <Core/EngineObject.hpp>
#include <Core/Scene.hpp>
#include <Core/Settings.hpp>

namespace jej
{
    std::vector<std::shared_ptr<CollisionComponent>> CollisionSystem::m_components;

    CollisionSystem::CollisionSystem()
    {

    }
    //////////////////////////////////////////


    CollisionSystem::~CollisionSystem()
    {

    }
    //////////////////////////////////////////


    CollisionSystem& CollisionSystem::GetInstance()
    {
        static CollisionSystem instance;
        return instance;
    }
    //////////////////////////////////////////


    void CollisionSystem::_update(const float)
    {
        const auto* scene = EngineObject::GetInstance().GetCurrentScene();

        for (const auto& AllComponents : m_components)
        {
            for (const auto& ShapeCompItr : ShapeSystem::GetInstance()._getComponentsRef<ShapeComponent>())
            {
                if (AllComponents->m_parentID == ShapeCompItr->GetParentID())
                {
                    AllComponents->m_AABB = Math::ConvexCollisionBox(*ShapeCompItr,
                        scene->GetEntityPtr(AllComponents->m_parentID)->
                        GetComponentPtr<TransformComponent>()->position);
                }
            }
        }


        for (unsigned int i = 0u; i < m_components.size(); ++i)
        {
            const Vector2f firstMin = m_components[i].get()->m_AABB.first;
            const Vector2f firstMax = m_components[i].get()->m_AABB.second;

            for (unsigned int j = (i + 1u); j < m_components.size(); ++j)
            {
                const Vector2f secondMin = m_components[j].get()->m_AABB.first;
                const Vector2f secondMax = m_components[j].get()->m_AABB.second;


                if (firstMin.x < (secondMin.x + (secondMax.x - secondMin.x)) &&
                    secondMin.x < (firstMin.x + (firstMax.x - firstMin.x)) &&

                    firstMin.y < (secondMin.y + (secondMax.y - secondMin.y)) &&
                    secondMin.y < (firstMin.y + (firstMax.y - firstMin.y)))
                {
                    // Collision happening if all are true
                    Messenger::Add(Messenger::MessageType::Info, "Collision detected between entities: " + std::to_string(m_components[i]->GetParentID()) + " and " + std::to_string(m_components[j]->GetParentID()));

                    m_components[i]->IsColliding = true;
                    m_components[j]->IsColliding = true;
                }
                //TODO: fix
             //   else
             //   {
             //       m_components[i]->IsColliding = false;
             //       m_components[j]->IsColliding = false;
             //   }
            }
            int a = 0;
            ++a;
        }













    }
    //////////////////////////////////////////


    bool CollisionSystem::_finalize()
    {
        //TODO:
        return true;
    }
    //////////////////////////////////////////

    bool CollisionSystem::_initialize()
    {
        //TODO:
        return true;
    }
    //////////////////////////////////////////

}