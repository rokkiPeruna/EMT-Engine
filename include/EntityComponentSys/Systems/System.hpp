#ifndef JEJ_SYSTEM_HPP
#define JEJ_SYSTEM_HPP

//
#include <tuple>
#include <vector>
//

//
#include <EntityComponentSys/Components/TransformComponent.hpp>
//

namespace jej
{
    class System
    {

        //For accessing m_components
        friend class Scene;

    public:
        
        //Constructor
        System();

        //Disabled copy-constructors
        System(const System&) = delete;
        System operator=(const System&) = delete;

        //Destructor
        virtual ~System();

    protected:

        //Overloaded
        std::vector<std::shared_ptr<Component>> m_components;


    };
}

#endif