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

        //For modifying containers
        friend class UserSystem;

    private:

        //Singleton constructor
        System();

    public:
        
        //Disabled copy-constructors
        System(const System&) = delete;
        System operator=(const System&) = delete;

        //Destructor
        virtual ~System();

    };
}

#endif