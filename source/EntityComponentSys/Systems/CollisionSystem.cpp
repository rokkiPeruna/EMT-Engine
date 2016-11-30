#include <EntityComponentSys/Systems/CollisionSystem.hpp>



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
		for (const auto& itr : m_components)
		{
			// TODO: Collision detection, "insert magic here"..

		}
	}

}