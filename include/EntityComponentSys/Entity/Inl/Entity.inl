template<typename T, typename ... Args>
bool Entity::AddComponent(Args ... p_args)
{
    if (HasComponent<T>())
    {
        Messenger::Add(Messenger::MessageType::Error, "Entity: ", m_name, "ID: ", m_entityID, " already has a component");
        return false;   //Component of this type already linked to the entity
    }

    auto& components = std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components;    //Get m_components from correct system
    components.emplace_back(std::make_shared<T>(std::forward<Args>(p_args)...));    //Create component
    components.back()->setParent(m_entityID);   //Parent the newborn component to this entity
    m_componentIDs.emplace_back(Component::m_componentIDCounter - 1u);  //Take responsibility of the component

    return true;
}


template <typename T>
T* Entity::GetComponentPtr()
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to get component that doesn't inherit from Component.");

    for (auto i : std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components)
        if (i->m_parentID == m_entityID)
            return i.get();

    return nullptr;
}


template <typename T>
const T* Entity::GetComponentPtr() const
{
    return GetComponentPtr<T>();
}


template <typename T>
bool Entity::HasComponent()
{
    for (auto i : std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components)
        if (i->m_parentID == m_entityID)
            return true;

    return false;
}


template <typename T>
bool Entity::RemoveComponent()
{
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

