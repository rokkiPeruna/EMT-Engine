template <typename ... Args>
RenderComponent::RenderComponent(Entity& entity, const Args& ... args) :
Component(entity),
m_shaderComp(nullptr),
m_shapeComp(nullptr),
m_transformComp(nullptr)
{
    //Add components from args
    //TAKES THE COMPONENTS IN AS RAW OBJECTS
    _addComponent(entity, args...);

    //Create default components
    if (!m_shaderComp)
    {
        _createDefault<ShaderComponent>(entity, m_shaderComp);
    }
    if (!m_shapeComp)
    {
        _createDefault<ShapeComponent>(entity, m_shapeComp);
    }
    if (!m_transformComp)
    {
        _createDefault<TransformComponent>(entity, m_transformComp);
    }


    JEJ_ASSERT(m_shaderComp.get() != nullptr, "ShaderComponent not initialized.");
    JEJ_ASSERT(m_shapeComp.get() != nullptr, "ShapeComponent not initialized.");
    JEJ_ASSERT(m_transformComp.get() != nullptr, "TransformComponent not initialized.");

    //Assign component type
    m_componentType = ComponentType::Render;
}
//////////////////////////////////////////

template <typename T>
void RenderComponent::_createDefault(Entity& p_entity, std::shared_ptr<T>& p_ptr)
{
    auto& components = std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components;

    for (auto itr : components)
    {
        if (itr->m_parentID == p_entity.m_entityID)
        {
            //Entity has a component of type T already bound to it
            p_ptr = itr;
            return;
        }
    }
    
    //Entity does not have a component of type T, create it
    components.emplace_back(std::make_shared<T>(p_entity));
    p_ptr = components.back();
}
//////////////////////////////////////////


template <typename T>
void RenderComponent::_addComponentTrue(Entity& entity, const T& t)
{
    //Check if the entity has a component of type T
    for (auto itr : std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components)
    {
        if (itr->m_parentID == entity.m_entityID)
        {
            break;
        }
    }

    //Parent entity of 't' IS NOT same as given entity
    if (&entity != EngineObject::GetInstance().GetSceneRef()->GetEntityPtr(t.m_parentID))
    {
        Messenger::Add(Messenger::MessageType::Debug,
            "RenderComponent: Given component is not parented to given entity.",
            "This might cause undefined behaviour",
            "Entity gets the component added to itself, but the component keeps its old parent.");

        //Add a notation of the component to the entity
        //Now two entities might share same component
        entity.m_componentIDs.emplace_back(t.m_componentID);

        //Do we want to create copies of the entities
        //Messenger::Add(Messenger::MessageType::Debug, "RenderComponent: Given component is not parented to given entity.", "Creating a copy of given component");
        //std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->emplace_back();
    }
#ifdef JEJ_DEBUG_MODE
    else
    {
        Messenger::Add(Messenger::MessageType::Debug, "RenderComponent: Component is already parented to given entity.");
    }
#endif
    return;
}
//////////////////////////////////////////


template <typename T>
void RenderComponent::_addComponentImpl(Entity&, const T&)
{
    static_assert(false, "RenderComponent: Bad argument type");
}
//////////////////////////////////////////


template <>
void RenderComponent::_addComponentImpl<ShaderComponent>(Entity& entity, const ShaderComponent& t)
{
    //If several ShaderComponents have been passed
    if (m_shaderComp)
    {
        Messenger::Add(Messenger::MessageType::Error, "RenderComponent: ShaderComponent already bound, bypassing.");
        JEJ_ASSERT(false, "RenderComponent: ShaderComponent already bound.");
        return;
    }
    _addComponentTrue<ShaderComponent>(entity, t);
}
//////////////////////////////////////////


//TODO: This is second definition, see above!
//template <>
//void RenderComponent::_addComponentImpl<ShapeComponent>(Entity& entity, const ShapeComponent& t)
//{
//    //If several ShapeComponents have been passed
//    if (m_shapeComp)
//    {
//        Messenger::Add(Messenger::MessageType::Error, "RenderComponent: ShapeComponent already bound, bypassing.");
//        JEJ_ASSERT(false, "RenderComponent: ShapeComponent already bound.");
//        return;
//    }
//    _addComponentTrue<ShapeComponent>(entity, t);
//}
//////////////////////////////////////////


template <>
void RenderComponent::_addComponentImpl<TransformComponent>(Entity& entity, const TransformComponent& t)
{
    //If several ShaderComponents have been passed
    if (m_transformComp)
    {
        Messenger::Add(Messenger::MessageType::Error, "RenderComponent: TransformComponent already bound, bypassing.");
        JEJ_ASSERT(false, "RenderComponent: TransformComponent already bound.");
        return;
    }
    _addComponentTrue<TransformComponent>(entity, t);
}
//////////////////////////////////////////


template <typename T, typename ... Args>
void RenderComponent::_addComponentHelper(Entity& entity, const T& t, const Args& ... args)
{
    static_assert(std::is_base_of<Component, T>::value, "Tried to add a component to RenderComponent that does not inherit from Component");
    _addComponentImpl<T>(entity, t);
    _addComponent<Args...>(entity, args...);
}
//////////////////////////////////////////


template <typename ... Args>
void RenderComponent::_addComponent(Entity& entity, const Args& ... args)
{
    _addComponentHelper<Args...>(entity, args...);
}
//////////////////////////////////////////


template <>
void RenderComponent::_addComponent<>(Entity&)
{

}
//////////////////////////////////////////

