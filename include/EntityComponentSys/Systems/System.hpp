#ifndef JEJ_SYSTEM_HPP
#define JEJ_SYSTEM_HPP

//
#include <memory>
#include <vector>
//

//
#include <EntityComponentSys/Components/TransformComponent.hpp>
//

namespace jej
{
    //
    class Entity;
    //

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

        //Static container for each sub system to scroll through
        static std::vector<std::shared_ptr<Entity>> m_entities;
    };
}

#endif