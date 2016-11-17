#ifndef JEJ_SYSTEM_HPP
#define JEJ_SYSTEM_HPP

#include <Core/BaseStructs.hpp>
#include <Core/EngineObject.hpp>

//
#include <memory>
#include <vector>
//

//
//

namespace jej
{
    //For m_components
    class Component;

    class System
    {

        //For accessing m_components
        friend class Scene;

    public:
        
        //Constructor
        System();

        //Disabled copy-constructors
        //System(const System&) = delete;
        //System operator=(const System&) = delete;

        //Destructor
        virtual ~System();

        virtual void update(const float p_deltaTime) = 0;

    protected:

        //Overloaded
        std::vector<std::shared_ptr<Component>> m_components;

        //Get component vector reference of desired type
        template <typename T>
        std::vector<std::shared_ptr<T>>& getComponentsRef();



    };

#include <EntityComponentSys/Systems/Inl/System.inl>

}

#endif