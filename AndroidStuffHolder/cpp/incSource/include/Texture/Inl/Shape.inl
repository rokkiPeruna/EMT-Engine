template <typename ... Args>
Shape::Shape(const Args& ... p_args):
m_ID(++m_ShapeIDCounter),
m_points(),
m_shapeType()
{
	texID = 0;
    _addShape(p_args...);
}