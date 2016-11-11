#include <EntityComponentSys/Components/Component.hpp>


namespace jej
{

    unsigned int Component::m_componentIDCounter = 0u;
    unsigned int Component::m_componentIDRemovedCounter = 0u;

    Component::Component() :
        m_componentType(),
        m_componentID(++m_componentIDCounter),
        m_parentEntityID()
    {

    }

    Component::Component(const Component& p_other):
        m_componentID(++m_componentIDCounter),
        m_parentEntityID(p_other.m_parentEntityID)
    {

    }

    Component& Component::operator=(const Component& p_other)
    {
        m_componentID = ++m_componentIDCounter;
        m_parentEntityID = p_other.m_parentEntityID;
        return *this;
    }

    Component::~Component()
    {
        ++m_componentIDRemovedCounter;
    }
    //
}