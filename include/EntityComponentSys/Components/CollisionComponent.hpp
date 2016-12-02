#ifndef JEJ_COLLISION_COMPONENT_HPP
#define JEJ_COLLISION_COMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>
#include <EntityComponentSys/Components/TransformComponent.hpp>


namespace jej
{
	
	class Shape;
	class CollisionComponent : public Component
	{
		friend class CollisionSystem;

	public:

		CollisionComponent::CollisionComponent(Entity* p_entity, const Shape* p_shape);

		CollisionComponent::~CollisionComponent();

		CollisionComponent(const CollisionComponent&) = delete;
		CollisionComponent operator=(const CollisionComponent&) = delete;



	private:

		Vector2f m_min;
		Vector2f m_max;

	};



}

#endif