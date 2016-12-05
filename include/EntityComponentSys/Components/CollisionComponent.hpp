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

        //Constructor
        CollisionComponent(Entity* p_entity);

        //Disabled copy-constructors
        NOCOPY(CollisionComponent);

        //Destructor
        ~CollisionComponent();


    private:

        Vector2f m_min;
        Vector2f m_max;

    };



}

#endif