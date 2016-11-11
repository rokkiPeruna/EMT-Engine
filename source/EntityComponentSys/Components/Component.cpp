#include <EntityComponentSys/Components/Component.hpp>


namespace jej
{

    unsigned int Component::m_IDCounter = 0u;
    unsigned int Component::m_IDRemovedCounter = 0u;

    Component::Component() :
        ID(m_IDCounter)
    {
        ++m_IDCounter;
    }
    //

    Component::~Component()
    {
        ++m_IDRemovedCounter;
    }
    //
}