#include <EntityComponentSys/Systems/CollisionSystem.hpp>
#include <Utility/Messenger.hpp>


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
					Messenger::Add(Messenger::MessageType::Info, "Collision detected");
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