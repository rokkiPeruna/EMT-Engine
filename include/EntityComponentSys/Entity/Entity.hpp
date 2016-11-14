#ifndef JEJ_ENTITY_HPP
#define JEJ_ENTITY_HPP

//
#include <memory>
#include <string>
#include <vector>
//


namespace jej
{

    class Entity
    {
        //For manipulating components
        friend class Scene;

        //For debugging memory
        friend class EngineObject;

        //For componentIDs
        friend class Component;

    public:
        
        Entity(const std::string& p_name = "");

        Entity(const Entity&) = delete;
        Entity operator=(const Entity&) = delete;

        virtual ~Entity();

        void* userData;

        const unsigned int GetID() const;

    private:

        const std::string m_name;

        unsigned int m_entityID;

        static unsigned int m_entityIDCounter;
        static unsigned int m_entityIDRemovedCounter;

        std::vector<unsigned int> m_componentIDs;

    };
}

#endif
