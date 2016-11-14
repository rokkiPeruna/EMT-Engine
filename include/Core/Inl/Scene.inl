
template<typename T, typename ... Args>
bool Scene::AddComponent(Entity& p_entity, Args ... p_args)
{
    //Component of this type already linked to the entity
    if (HasComponent<T>(p_entity))
        return false;

    //If not, add component
    const bool isBase = std::is_base_of<Component, T>::value;
    if (!isBase)
    {
        Messenger::Add(Messenger::MessageType::Error, "Tried to create component that doesn't inherit from Component. Target Entity: ", p_entity.m_name);
        static_assert(isBase, "Tried to create component that doesn't inherit from Component.");
    }

    //Get components vector from correct system
    auto& components = _getComponentVectorFromSystem<T>();

    //Create component
    components.emplace_back(std::make_shared<T>(std::forward<Args>(p_args)...));

    return true;

}


template <typename T>
T* Scene::GetComponentPtr(Entity& p_entity)
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to get component that doesn't inherit from Component.");

    for (const auto& itr : p_entity.m_componentIDs)
        if (itr == )
            return reinterpret_cast<T*>(itr);

    return nullptr;
}

template <typename T>
const T* Scene::GetComponentPtr(const Entity& p_entity, const ComponentType p_compType)
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to get component that doesn't inherit from Component.");

    for (const auto& itr : p_entity.m_components)
        if (itr->m_componentType == p_compType)
            return reinterpret_cast<T*>(itr.get());

    return nullptr;

}

template <typename T>
bool HasComponent(const Entity& p_entity)
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to check if Entity has a component that doesn't inherit from Component.");

    auto& components = _getComponentVectorFromSystem<T>();

    for (auto itrID : p_entity.m_componentIDs)
        for (auto itrComp : components)
            if (itrID == (dynamic_cast<Component>(itrComp)).m_componentID)
                return true;

    return false;
}

template <typename T>
bool RemoveComponent(Entity& p_entity)
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to remove a component that doesn't inherit from Component.");

    auto& components = _getComponentVectorFromSystem<T>();

    for (auto itrID = p_entity.m_components.begin(); itrID != p_entity.m_components.end(); ++itrID)
        for (auto itrComps = components.begin(); itrComps != components.end(); ++itrComps)
            if (itr == itrComps)
            {
                p_entity.m_components.erase(itrID);
                components.erase(itrComps);
                return true;
            }

    Messenger::Add(Messenger::MessageType::Debug, "Could not remove component from entity: ", p_entity.m_name);
    return false;
}

template <typename T>
std::vector<std::shared_ptr<T>>& _getComponentVectorFromSystem()
{
    switch (T)
    {
    case TransformComponent:
        return TransformSystem::GetInstance().m_components;
        break;

    case RenderComponent:
        return RenderSystem::GetInstance().m_components;
        break;

    default:
        JEJ_ASSERT(false, "All components && systems here");
        char a = 'a';
        return a;
        break;
    }
}