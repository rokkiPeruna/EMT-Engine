#ifndef JEJ_COMPONENT_HPP
#define JEJ_COMPONENT_HPP

#include <Core/BaseStructs.hpp>

//One does not simply #include <Core/Settings.hpp> here

#include <string>
#include <vector>

namespace jej
{


    class Component
    {

        //For ID counter
        friend class EngineObject;

        //For manipulating components
        friend class Entity;

        //
        friend class RenderComponent;

		friend class CollisionComponent;

    public:

        //Constructor
        Component(Entity* entity);

        //Copy-constructor
        Component(const Component& p_other);

        //Assignment operator removed
        Component& operator=(const Component& p_other) = delete;

        //Destructor
        virtual ~Component();

    protected:

        void setParent(const JEJ_COUNT p_parentID);

        //Type of this
        ComponentType m_componentType;

        //ID of this
        const unsigned int m_componentID;

        //ID of the entity that owns this
        unsigned int m_parentID;

    private:

        static unsigned int m_componentIDCounter;
        static unsigned int m_componentIDRemovedCounter;
    };

}

#endif