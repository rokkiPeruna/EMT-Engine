#include <EntityComponentSys/Entity/Entity.hpp>

#include <EntityComponentSys/Systems/System.hpp>

#include <algorithm>

namespace jej
{

    unsigned int Entity::m_entityIDCounter = 0u;
    unsigned int Entity::m_entityIDRemovedCounter = 0u;

    Entity::Entity(const std::string& p_name) :
        m_name(p_name),
        m_entityID(++m_entityIDCounter),
        userData(nullptr)
    {

    }
    //

    Entity::~Entity()
    {
        ++m_entityIDRemovedCounter;
    }
    //

    const unsigned int Entity::GetID() const
    {
        return m_entityID;
    }

}