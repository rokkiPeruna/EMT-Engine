
template <typename T, typename ... Args>
T& ShapeComponent::AddShape(const ShapeType p_type, const Args& ... p_args)
{

    switch (p_type)
    {
    case ShapeType::Circle:
        m_shapes.emplace_back(std::make_shared<Circle>(std::forward<Args>(p_args)...));
        return  *m_shapes.back().get();
        break;

    case ShapeType::Convex:
        m_shapes.emplace_back(std::make_shared<Convex>(std::forward<Args>(p_args)...));
        return  *m_shapes.back().get();
        break;

    case ShapeType::Rectangle:
        m_shapes.emplace_back(std::make_shared<Circle>(std::forward<Args>(p_args)...));
        return  *m_shapes.back().get();
        break;

    case ShapeType::Triangle:
        m_shapes.emplace_back(std::make_shared<Circle>(std::forward<Args>(p_args)...));
        return  *m_shapes.back().get();
        break;

    default:
        static_assert(false, "Invalid ShapeType");

    }

}