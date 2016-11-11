
#include <EntityComponentSys/Systems/UserSystem.hpp>
#include <EntityComponentSys/Systems/System.hpp>
#include <Utility/Messenger.hpp>

#include <algorithm>

namespace jej
{

    UserSystem::UserSystem()
    {

    }

    UserSystem::~UserSystem()
    {

    }

    UserSystem& UserSystem::GetInstance()
    {
        static UserSystem system;
        return system;
    }

    //Public methods

    bool UserSystem::HasComponent(const Entity& p_entity, const ComponentType p_compType)
    {
        for (const auto& itr : p_entity.m_components)
            if (itr->m_componentType == p_compType)
                return true;

        return false;
    }

    bool UserSystem::RemoveComponent(Entity& p_entity, const ComponentType p_compType)
    {
        for (auto itr = p_entity.m_components.begin(); itr != p_entity.m_components.end(); ++itr)
            if (itr->get()->m_componentType == p_compType)
            {
                p_entity.m_components.erase(itr);
                return true;
            }

        Messenger::Add(Messenger::MessageType::Debug, "Component of type: ", p_compType, " not found on entity: ", p_entity.m_name);
        return false;
    }

}