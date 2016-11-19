template <typename ... Args>
RenderComponent::RenderComponent(const Entity& entity, const Args& ... args) :
Component(),
m_shaderComp(nullptr),
m_shapeComp(nullptr),
m_transformComp(nullptr)
{
    _addComponent(args...);

    if (!m_shaderComp)
        m_shaderComp.reset(new ShaderComponent());
    if (!m_shapeComp)
        m_shapeComp.reset(new ShapeComponent());
    if (!m_transformComp)
        m_transformComp.reset(new TransformComponent());


    JEJ_ASSERT(m_shaderComp.get() != nullptr, "ShaderComponent not initialized.");
    JEJ_ASSERT(m_shapeComp.get() != nullptr, "ShapeComponent not initialized.");
    JEJ_ASSERT(m_transformComp.get() != nullptr, "TransformComponent not initialized.");

    m_componentType = ComponentType::Render;
}

template <typename T>
void RenderComponent::_addComponentImpl(const T& t)
{
    if (T == std::shared_ptr<ShaderComponent> && m_shaderComp == nullptr)
    {
        m_shaderComp = std::static_pointer_cast<ShaderComponent>(t);
    }
    else if (T == std::shared_ptr<ShapeComponent> && m_shapeComp == nullptr)
    {
        m_shapeComp = std::static_pointer_cast<ShapeComponent>(t);
    }
    else if (T == std::shared_ptr<TransformComponent> && m_transformComp == nullptr)
    {
        m_transformComp = std::static_pointer_cast<TransformComponent>(t);
    }
    else
    {
        Messenger::Add(Messenger::MessageType::Error, "RenderComponent: Bad argument");
    }
}

template <typename T, typename ... Args>
void RenderComponent::_addComponentHelper(const T& t, const Args& ... args)
{
    _addComponentImpl<T>(t);
    _addComponent<Args...>(args...);
}

template <typename ... Args>
void RenderComponent::_addComponent(const Args& ... args)
{
    _addComponentHelper<Args...>(args...);
}

template <>
void RenderComponent::_addComponent<>()
{

}
