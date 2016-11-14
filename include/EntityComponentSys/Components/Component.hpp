#ifndef JEJ_COMPONENT_HPP
#define JEJ_COMPONENT_HPP

#include <Core/BaseStructs.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>

#include <string>
#include <vector>

namespace jej
{


    class Component
    {

        //For ID counter
        friend class EngineObject;

        //For manipulating components
        friend class Scene;

    public:

        //Constructor
        Component();

        //Copy-constructors
        Component(const Component& p_other);

        Component& operator=(const Component& p_other);

        //Destructor
        virtual ~Component();

    protected:

        //What am I
        ComponentType m_componentType;

        //Who am I
        unsigned int m_componentID;

        virtual std::vector<unsigned int>& getComponentIDsRef() final;

    private:

        static unsigned int m_componentIDCounter;
        static unsigned int m_componentIDRemovedCounter;
    };

   

#include <EntityComponentSys/Components/Inl/Component.inl>

}

#endif