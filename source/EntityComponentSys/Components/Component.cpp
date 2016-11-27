#include <EntityComponentSys/Components/Component.hpp>

#include <Core/EngineObject.hpp>
#include <Core/Scene.hpp>

namespace jej
{

    unsigned int Component::m_componentIDCounter = 0u;
    unsigned int Component::m_componentIDRemovedCounter = 0u;

    Component::Component(Entity* entity) :
        m_componentType(ComponentType::Failure),
        m_componentID(++m_componentIDCounter),
        m_parentID(entity->m_entityID)
    {

        //Entity takes
        entity->m_componentIDs.emplace_back(m_componentID);
    }
    ///////////////////////////////////


    Component::Component(const Component& p_other) :
        m_componentType(p_other.m_componentType),
        m_componentID(++m_componentIDCounter),
        m_parentID(p_other.m_parentID)
    {
        //Messes up componentIDs whether incremented or not

        //Don't comment this out, your code is probably flawed if it comes here
        DebugBreak();
    }
    ///////////////////////////////////


    Component::~Component()
    {
        ++m_componentIDRemovedCounter;
    }
    ///////////////////////////////////


    void Component::setParent(const JEJ_COUNT p_parentID)
    {
        m_parentID = p_parentID;
    }
    ///////////////////////////////////


}