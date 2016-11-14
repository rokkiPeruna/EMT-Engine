template<typename ... Args>
bool Entity::AddComponent(const ComponentType p_type, Args ... p_args)
{
    //Component of this type already linked to the entity
    if (HasComponent(p_type))
    {
        Messenger::Add(Messenger::MessageType::Error, "Entity: ", m_name, "ID: ", m_entityID, " already has a component of type: ", (unsigned short int)p_type);
        return false;
    }

    //TYÖMAA

    //Add all systems here
    switch (p_type)
    {
    case ComponentType::Transform:
        TransformSystem::GetInstance().m_components.emplace_back(std::make_shared<TransformComponent>(m_entityID, std::forward<Args>(p_args)...));
        break;

    default:
        break;
    }

    return true;

}


template <typename T>
T* Entity::GetComponentPtr(const ComponentType p_type)
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to get component that doesn't inherit from Component.");

    //TYÖMAA

    //Add all systems
    switch (p_type)
    {
    case ComponentType::Transform:
        for (auto i : TransformSystem::GetInstance().m_components)
            if (i->m_parentID == m_entityID)
                return i.get();


    case ComponentType::Failure:
    default:
        return nullptr;
    }

}

template <typename T>
const T* Entity::GetComponentPtr(const ComponentType p_type) const
{
    return GetComponentPtr(p_type);
}

