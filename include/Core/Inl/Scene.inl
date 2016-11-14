

template <typename T>
std::vector<std::shared_ptr<T>>& Scene::_getComponentVectorFromSystem()
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

template <typename T>
T* Scene::_getComponentPtr(const unsigned int p_ID)
{

    std::vector<std::shared_ptr<T>>* components = nullptr;

    switch (T)
    {
    case TransformComponent:
        components = &TransformSystem::GetInstance().m_components;
        break;

    default:
        break;
    }

    if (!components)
    {
        Messenger::Add(Messenger::MessageType::Error, "Unresolved Component / System type.");
        return nullptr;
    }

    //  for (auto itr : components)
    //        itr->



}


template <typename T>
bool Scene::_hasComponent(const unsigned int p_ID)
{

    switch (T)
    {
    case TransformComponent:
        for (auto itr : TransformSystem::GetInstance().m_components)
            if (itr->)
                break;

    default:
        break;
    }

}
