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
        friend class UserSystem;
    private:
    public:
        //Default constructor
        System();
        

        //Disabled copy-constructors
        //System(const System&) = delete;
        //System operator=(const System&) = delete;

        //Destructor
        virtual ~System();


        virtual void Update() = 0;

        //Static container for each sub system to scroll through
        static std::vector<std::shared_ptr<Entity>> m_entities;
        std::vector<std::shared_ptr<Component>> m_components;

        //Get component vector reference of desired type
        template <typename T>
        std::vector<std::shared_ptr<T>>& getComponentsRef();



    };

#include <EntityComponentSys/Systems/Inl/System.inl>

}

#endif