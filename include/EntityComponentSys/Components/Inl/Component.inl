
template<typename T, typename ... Args>
bool AddComponent(Entity& p_entity, const ComponentType p_compType, Args ... p_args)
{
    //Component of this type already linked to the entity
    if (HasComponent(p_entity, p_compType))
        return false;

    //If not, add component
    const bool isBase = std::is_base_of<Component, T>::value;
    if (!isBase)
    {
        Messenger::Add(Messenger::MessageType::Error, "Tried to create component that doesn't inherit from Component. Target Entity: ", p_entity.m_name);
        static_assert(isBase, "Tried to create component that doesn't inherit from Component.");
    }

    p_entity.m_components.emplace_back(std::make_shared<T>(std::forward<Args>(p_args)...));
    return true;

}


template <typename T>
T* GetComponentPtr(Entity& p_entity, const ComponentType p_compType)
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to get component that doesn't inherit from Component.");

    for (const auto& itr : p_entity.m_components)
        if (itr->m_componentType == p_compType)
            return reinterpret_cast<T*>(itr.get());

    return nullptr;
}

template <typename T>
const T* GetComponentPtr(const Entity& p_entity, const ComponentType p_compType)
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to get component that doesn't inherit from Component.");

    for (const auto& itr : p_entity.m_components)
        if (itr->m_componentType == p_compType)
            return reinterpret_cast<T*>(itr.get());

    return nullptr;

}