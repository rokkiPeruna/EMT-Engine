

template<typename T, typename ... Args>
T& Entity::AddComponent(Args ... p_args)
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
/////////////////////////////////////////


template <typename T>
T* Entity::GetComponentPtr()
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to get component that doesn't inherit from Component.");

    for (auto& i : std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components)
        if (i->GetParentID() == m_entityID)
            return i.get();

    return nullptr;
}
/////////////////////////////////////////


template <typename T>
const T* Entity::GetComponentPtr() const
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to get component that doesn't inherit from Component.");

    for (const auto& i : std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components)
        if (i->GetParentID() == m_entityID)
            return i.get();

    return nullptr;
}
/////////////////////////////////////////


template <typename T>
bool Entity::HasComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to compare component that doesn't inherit from Component.");

    for (const auto& i : std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components)
        if (i->GetParentID() == m_entityID)
            return true;

    return false;
}
/////////////////////////////////////////


template <typename T>
bool Entity::RemoveComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to remove component that doesn't inherit from Component.");

    JEJ_COUNT removedID = 0u;

    auto& v = std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components;

    for (auto itr = v.begin(); itr != v.end(); ++itr)
        if (itr->get()->GetParentID() == m_entityID)
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
/////////////////////////////////////////

template <>
bool Entity::RemoveComponent()
{

}

namespace detail
{
    
    //Helpers

    //Base
    template<int...>
    struct tupleIndex
    {

    };

    //Forward declaration
    template<int I, typename Index, typename... Types>
    struct makeIndicesImpl;


    template<int I, int... Indices, typename T, typename ... Types>
    struct makeIndicesImpl<I, tupleIndex<Indices...>, T, Types...>
    {
        typedef typename makeIndicesImpl<I + 1, tupleIndex<Indices..., I>, Types...>::type type;
    };


    template<int I, int... Indices>
    struct makeIndicesImpl<I, tupleIndex<Indices...> >
    {
        typedef tupleIndex<Indices...> type;
    };

    //Empty
    template<typename ... Types>
    struct makeIndices : makeIndicesImpl<0, tupleIndex<>, Types...>
    {

    };

    //Helpers end


    //Iteration

    //Last args
    template<typename Func, typename Last>
    void _forEachImpl(Func&& p_func, Last&& p_last)
    {
        p_func(p_last);
    }

    //Multiple args
    template<typename Func, typename First, typename ... Rest>
    void _forEachImpl(Func&& p_func, First&& p_first, Rest&& ... p_rest)
    {
        p_func(p_first);
        _forEachImpl(std::forward<Func>(p_func), p_rest...);
    }

    //Open args
    template<typename Func, int ... Indices, typename ... Args>
    void _forEachHelper(Func&& p_func, tupleIndex<Indices...>, std::tuple<Args...>&& p_tuple)
    {
        _forEachImpl(std::forward<Func>(p_func), std::forward<Args>(std::get<Indices>(p_tuple))...);
    }

    //Core
    template<typename Func, typename ... Args>
    void ForTuple(std::tuple<Args...>& p_tuple, Func&& p_func)
    {
        _forEachHelper(std::forward<Func>(p_func),
            typename makeIndices<Args...>::type(),
            std::forward<std::tuple<Args...>>(p_tuple));
    }

    //Iteration end

}