
template<typename T, typename ... Args>
inline T& Entity::AddComponent(Args ... p_args)
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to create component that doesn't inherit from Component.");

    if (HasComponent<T>())
    {
        Messenger::Add(Messenger::MessageType::Error, "Entity: ", m_name, "ID: ", m_entityID, " already has a component");
        return *GetComponentPtr<T>();   //Component of this type already linked to the entity
    }

    auto& components = std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components;    //Get m_components from correct system
    components.emplace_back(std::make_shared<T>(this, std::forward<Args>(p_args)...));    //Create component

    return *components.back().get();
}


template <typename T>
inline T* Entity::GetComponentPtr()
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to get component that doesn't inherit from Component.");

    for (auto i : std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components)
        if (i->m_parentID == m_entityID)
            return i.get();

    return nullptr;
}


template <typename T>
inline const T* Entity::GetComponentPtr() const
{
    return GetComponentPtr<T>();
}


template <typename T>
inline bool Entity::HasComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to compare component that doesn't inherit from Component.");

    for (auto i : std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components)
        if (i->m_parentID == m_entityID)
            return true;

    return false;
}


template <typename T>
inline bool Entity::RemoveComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to remove component that doesn't inherit from Component.");

    JEJ_COUNT removedID = 0u;

    auto& v = std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components;

    for (auto itr = v.begin(); itr != v.end(); ++itr)
        if (itr->get()->m_parentID == m_entityID)
        {
            removedID = itr->get()->m_componentID;  //Remember what component was removed
            v.erase(itr);   //Remove component
            break;
        }

    for (size_t i = 0u; i < m_componentIDs.size(); ++i)
        if (m_componentIDs[i] == removedID)
        {
            m_componentIDs.erase(m_componentIDs.begin() + i);    //Remove component ID
            return true;    //Component removed
        }

    return false;
}

