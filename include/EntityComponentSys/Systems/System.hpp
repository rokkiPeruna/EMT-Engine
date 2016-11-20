#ifndef JEJ_SYSTEM_HPP
#define JEJ_SYSTEM_HPP

#include <Core/BaseStructs.hpp>
#include <Core/EngineObject.hpp>

//
#include <memory>
#include <vector>
//

//
#include <EntityComponentSys/Components/TransformComponent.hpp>
//

namespace jej
{
    //For m_components
    class Component;

    //
    class Entity;
    //

    class System
    {

        //For modifying containers
        friend class RenderComponent;

    public:
        
		//Default constructor
        System();
        
        //Destructor
        virtual ~System();

protected:

    //Update
    virtual void _update(const float p_deltaTime) = 0;

    //Overloaded
    //std::vector<std::shared_ptr<Component>> m_components;

    //Get component vector reference of desired type
    template <typename T>
    std::vector<std::shared_ptr<T>>& _getComponentsRef();

    };

#include <EntityComponentSys/Systems/Inl/System.inl>

}

#endif