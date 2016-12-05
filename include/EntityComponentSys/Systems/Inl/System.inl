
template <typename T>
std::vector<std::shared_ptr<T>>& System::_getComponentsRef()
{
    return std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components;
}

template <typename T>
const std::vector<std::shared_ptr<T>>& System::_getComponentsRef() const
{
    return std::get<ComponentHelper<T>::index>(EngineObject::GetInstance().m_systems)->m_components;
}