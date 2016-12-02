#ifndef JEJ_COLLISION_SYSTEM_HPP
#define JEJ_COLLISION_SYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>
#include <EntityComponentSys/Components/CollisionComponent.hpp>

namespace jej
{
	class CollisionSystem : public System
	{

	private:

		CollisionSystem();

		
	public:

		~CollisionSystem();

		static CollisionSystem& GetInstance();
		void _update(const float deltaTime);
		
		static std::vector<std::shared_ptr<CollisionComponent>> m_components;
	};



}

#endif