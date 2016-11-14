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

    public:

        //Constructor
        Component(const JEJ_COUNT p_parentID);

        //Copy-constructor
        Component(const Component& p_other);

        //Assignment operator removed
        Component& operator=(const Component& p_other) = delete;

        //Destructor
        virtual ~Component();

    protected:

        //What am I
        ComponentType m_componentType;

        //Who am I
        const unsigned int m_componentID;

        //Who the hell are you
        const unsigned int m_parentID;

    private:

        static unsigned int m_componentIDCounter;
        static unsigned int m_componentIDRemovedCounter;
    };

}

#endif