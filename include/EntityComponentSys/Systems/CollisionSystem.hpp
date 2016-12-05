#ifndef JEJ_COLLISION_SYSTEM_HPP
#define JEJ_COLLISION_SYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>
#include <EntityComponentSys/Components/CollisionComponent.hpp>

namespace jej
{
	class CollisionSystem : public System
	{
		// Declaration of friend classes
        friend class EngineObject;
        friend class Entity;
        
	private:

		// Singleton constructor
		CollisionSystem();

		
	public:

		// Deletion of copy constructor and copy assingment operator
        CollisionSystem(const CollisionSystem&) = delete;
        CollisionSystem operator=(const CollisionSystem) = delete;

		// Destructor
		~CollisionSystem();

		static CollisionSystem& GetInstance();
		
    protected:

		// Virtual method inherited from system, This is used to calculate the actual AABB collision
		// between 2 objects
        void _update(const float deltaTime) override;

		// Virtual method inherited from System
        bool _finalize() override;

		// Virtual method inherited from System
        bool _initialize() override;

		// Contains all collision component
        static std::vector<std::shared_ptr<CollisionComponent>> m_components;

	};



}

#endif