#include <EntityComponentSys/Entity/Entity.hpp>

#include <Core/EngineObject.hpp>

//#include <EntityComponentSys/Systems/TransformSystem.hpp>

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

        //Entity takes care of it's components
        RemoveAllComponents();
    }
    //

    const unsigned int Entity::GetID() const
    {
        return m_entityID;
    }


    bool Entity::RemoveAllComponents()
    {
        //TODO: Call remove on all types
        RemoveComponent<TransformComponent>();

        if (m_componentIDs.empty())
            return true;
        return false;
    }

}