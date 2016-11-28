template <typename ... Args>
Shape& ShapeComponent::AddShape(const Args& ... p_args)
{
    m_shapes.emplace_back(std::make_shared<Shape>(p_args...));
    return *m_shapes.back().get();
}