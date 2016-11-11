#include <EntityComponentSys/Entity.hpp>


namespace jej
{
    Entity::Entity()
    {

    }
    //

    Entity::~Entity()
    {

    }
    //

    //Public methods
    template<typename Args>
    bool Entity::AddComponent(ComponentType p_compType, Args ... args)
    {
        //Check if entity already has a given component type
            //

        //If not, add component
            //Switch-case
    }
}