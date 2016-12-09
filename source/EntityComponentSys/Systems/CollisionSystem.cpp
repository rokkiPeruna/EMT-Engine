#include <EntityComponentSys/Systems/ShapeSystem.hpp>
#include <EntityComponentSys/Systems/CollisionSystem.hpp>
#include <EntityComponentSys/Components/ShapeComponent.hpp>
#include <Utility/Math.hpp>
#include <Utility/Messenger.hpp>
#include <Core/EngineObject.hpp>
#include <Core/Scene.hpp>

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


	void CollisionSystem::_update(const float deltaTime)
	{
	
		for (const auto& AllComponents : m_components)
		{
			for (const auto& ShapeCompItr : ShapeSystem::GetInstance()._getComponentsRef<ShapeComponent>())
			{
				if (AllComponents->m_parentID == ShapeCompItr->GetParentID())
				{
					for (const auto& ShapeItr : ShapeCompItr.get()->m_shapes)
					{
						AllComponents->m_AABB = Math::ConvexCollisionBox(&*ShapeItr,
							EngineObject::GetInstance().GetCurrentScene()->
							GetEntityPtr(AllComponents->m_parentID)->
							GetComponentPtr<TransformComponent>()->position);
						break;
					}
					break;
				}
			}
		}

		for (int i = 0; i < m_components.size(); ++i)
		{
			const Vector2f firstMin = m_components[i].get()->m_AABB.first;
			const Vector2f firstMax = m_components[i].get()->m_AABB.second;

			for (int j = (i + 1); j < m_components.size(); ++j)
			{
				const Vector2f secondMin = m_components[j].get()->m_AABB.first;
				const Vector2f secondMax = m_components[j].get()->m_AABB.second;

				if (firstMin.x < (secondMin.x + (secondMax.x - secondMin.x)) &&
					secondMin.x < (firstMin.x + (firstMax.x - firstMin.x)) &&
					firstMin.y < (secondMin.y + (secondMax.y - secondMin.y)) &&
					secondMin.y < (firstMin.x + (firstMax.y - firstMin.y)))
				{
					// Collision happening if all are true
					Messenger::Add(Messenger::MessageType::Info, "Collision detected between " 
						,m_components[i]->GetID(), m_components[j]->GetID() );
					m_components[i]->isColliding = true;
					m_components[j]->isColliding = true;
				}
				else
				{
					m_components[i]->isColliding = false;
					m_components[j]->isColliding = false;
				}
			}
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