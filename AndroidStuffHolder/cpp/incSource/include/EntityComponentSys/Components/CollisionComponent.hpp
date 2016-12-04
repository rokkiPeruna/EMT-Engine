#ifndef JEJ_COLLISION_COMPONENT_HPP
#define JEJ_COLLISION_COMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>
#include <EntityComponentSys/Components/TransformComponent.hpp>



namespace jej
{
	class Entity;

	class CollisionComponent : public Component
	{
	public:

		CollisionComponent(Entity* p_entity, TransformComponent* p_transformComponent);

		~CollisionComponent();

		CollisionComponent(const CollisionComponent&) = delete;
		CollisionComponent operator=(const CollisionComponent&) = delete;

	private:

		jej::Vector2f m_position_min;
		jej::Vector2f m_position_max;

	};



}

#endif