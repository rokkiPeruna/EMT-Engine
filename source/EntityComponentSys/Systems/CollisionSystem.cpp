#include <EntityComponentSys/Systems/CollisionSystem.hpp>
#include <Utility/Messenger.hpp>


namespace jej
{
	CollisionSystem::CollisionSystem()
	{
	}

	CollisionSystem::~CollisionSystem()
	{
	}

	void CollisionSystem::_update(const float deltaTime)
	{


		for (int i = 0; i < m_components.size(); i++)
		{
		   	const Vector2f firstMin = m_components.at(i)->m_min;
			const Vector2f firstMax = m_components.at(i)->m_max;

			for (int j = (i + 1); j < m_components.size(); i++)
			{
				const Vector2f secondMin = m_components.at(j)->m_min;
				const Vector2f secondMax = m_components.at(j)->m_max;

				if (firstMin.x < (secondMin.x + (secondMax.x - secondMin.x)) &&
					secondMin.x < (firstMin.x + (firstMax.x - firstMin.x)) &&
					firstMin.y < (secondMin.y + (secondMax.y - secondMin.y)) &&
					secondMin.y < (firstMin.x + (firstMax.y - firstMin.y)))
				{
					// Collision happening if all are true?
					Messenger::Add(Messenger::MessageType::Info,
						"Collision detected between components (component ID 1:) " + m_components.at(i).get()->m_parentID,
						" and component (component ID 2: " + m_components.at(j).get()->m_parentID);
				}
			}
		}
	}
}