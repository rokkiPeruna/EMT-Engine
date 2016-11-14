#include <EntityComponentSys/Components/Component.hpp>

#include <Core/EngineObject.hpp>
#include <Core/Scene.hpp>

namespace jej
{

    unsigned int Component::m_componentIDCounter = 0u;
    unsigned int Component::m_componentIDRemovedCounter = 0u;

    Component::Component(const JEJ_COUNT p_parentID) :
        m_componentType(),
        m_componentID(++m_componentIDCounter),
        m_parentID(p_parentID)
    {

    }

    Component::Component(const Component& p_other) :
        m_componentID(++m_componentIDCounter),
        m_parentID(p_other.m_parentID)
    {
        //Think of some way to make sure parentId is correct
        DebugBreak();
    }

    Component::~Component()
    {
        ++m_componentIDRemovedCounter;
    }
    //

}