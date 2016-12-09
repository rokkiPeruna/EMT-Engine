#ifndef JEJ_COLLISION_COMPONENT_HPP
#define JEJ_COLLISION_COMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>
#include <EntityComponentSys/Components/TransformComponent.hpp>


namespace jej
{
	// Forward declaration of classes
	class Shape;


	class CollisionComponent : public Component
	{
		friend class CollisionSystem;
		friend class Entity;
	public:

		// Constructor
		CollisionComponent(Entity* p_entity);

		// Deletion of copy constructor and copy assingment operator 
		CollisionComponent(const CollisionComponent&) = delete;
		CollisionComponent operator=(const CollisionComponent&) = delete;
		
		// Destructor
		~CollisionComponent();


	private:

		// CollisionComponent's own parameters. Includes min and max value of the AABB box
		// for each CC.
		std::pair<Vector2f, Vector2f> m_AABB;
		JEJ_COUNT m_parentID;
		bool isColliding;
	};



}

#endif