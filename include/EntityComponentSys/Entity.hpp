#ifndef JEJ_ENTITY_HPP
#define JEJ_ENTITY_HPP

//
#include <memory>
#include <string>
#include <vector>
//


namespace jej
{

    class Component;

    class Entity
    {
        //For manipulating components
        friend class UserSystem;

        //For debugging memory
        friend class EngineObject;

    public:
        
        Entity(const std::string& p_name = "");

        Entity(const Entity&) = delete;
        Entity operator=(const Entity&) = delete;

        virtual ~Entity();

    private:

        const std::string m_name;

        unsigned int m_entityID;

        static unsigned int m_entityIDCounter;
        static unsigned int m_entityIDRemovedCounter;

        std::vector<std::shared_ptr<Component>> m_components;

    };


}

#endif
