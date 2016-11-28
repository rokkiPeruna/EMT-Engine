#ifndef JEJ_COLLISION_SYSTEM_HPP
#define JEJ_COLLISION_SYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>

namespace jej
{


	class CollisionSystem : public System
	{
		friend class CollisionComponent;

	private:

		CollisionSystem();

		

	public:

		~CollisionSystem();

		void GetInstance();
		void _update(const float deltaTime);
		
	};



}

#endif