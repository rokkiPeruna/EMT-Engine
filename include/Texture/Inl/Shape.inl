template <typename ... Args>
Shape::Shape(const Args& ... p_args):
m_ID(++m_ShapeIDCounter),
m_points(),
m_shapeType(),
m_radius(0u)
{
    _addShape(p_args...);
}