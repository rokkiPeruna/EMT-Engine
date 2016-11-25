#include <EntityComponentSys/Components/Shapes/Shape.hpp>

namespace jej
{

    int Shape::m_ShapeIDCounter = 0;
    int Shape::m_RemovedShapeIDCounter = 0;

    Shape::Shape():
        m_ID(++m_ShapeIDCounter),
        m_points(),
        m_shapeType(ShapeType::Failure)
    {
        
    }


    Shape::~Shape()
    {
        ++m_RemovedShapeIDCounter;
    }

    std::vector<Vector2f> Shape::GetPoints() const
    {
        return m_points;
    }

    bool Shape::SetPoints(const std::vector<Vector2f>& p_newPoints)
    {
        if (m_points.size() == p_newPoints.size())
        {
            m_points = p_newPoints;
            return true;
        }

        return false;
    }

    unsigned int Shape::GetID() const
    {
        return m_ID;
    }


}
