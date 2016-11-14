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

    public:
        //Default constructor
        System();

        //Disabled copy-constructors
        System(const System&) = delete;

        //Destructor
        virtual ~System();


        virtual void Update() = 0;

        //Static container for each sub system to scroll through
        static std::vector<std::shared_ptr<Entity>> m_entities;
    };
}

#endif