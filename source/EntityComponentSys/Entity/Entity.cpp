#include <EntityComponentSys/Entity/Entity.hpp>

//TYÖMAA

//Add all systems && corresponding components here
#include <EntityComponentSys/Systems/TransformSystem.hpp>
#include <EntityComponentSys/Components/TransformComponent.hpp>

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

    bool Entity::HasComponent(const ComponentType p_type)
    {

        //TYÖMAA

        //Add all systems here
        switch (p_type)
        {
        case ComponentType::Transform:
            for (auto i : TransformSystem::GetInstance().m_components)
                if (i->m_parentID == m_entityID)
                    return true;


        case ComponentType::Failure:
        default:
            return false;
        }
    }

    bool Entity::RemoveComponent(const ComponentType p_type)
    {
        JEJ_COUNT compID = 0u;


        //TYÖMAA

        //Add all systems here
        switch (p_type)
        {
        case ComponentType::Transform:
        {
            auto& v = TransformSystem::GetInstance().m_components;
            for (auto i = v.begin(); i != v.end(); ++i)
                if (i->get()->m_parentID == m_entityID)
                {
                    compID = i->get()->m_componentID; //Remember what component was removed
                    v.erase(i);
                    break;
                }
            break;
        }

        case ComponentType::Failure:
        default:
            Messenger::Add(Messenger::MessageType::Warning, "Component of type: ", (JEJ_COUNT)p_type, " could not be removed from Entity: ", m_name);
            return false;
        }

        for (JEJ_COUNT i = 0u; i < m_componentIDs.size(); ++i)
            if (m_componentIDs[i] == compID)
            {
                m_componentIDs.erase(m_componentIDs.begin() + i);
                return true; //Component removed
            }

        return false;
    }

    bool Entity::RemoveAllComponents()
    {
        for (JEJ_COUNT i = 0u; i < (JEJ_COUNT)ComponentType::SizeOfThis; ++i)
            RemoveComponent((ComponentType)i);

        return true;
    }

}