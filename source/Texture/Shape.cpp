#include <Texture/Shape.hpp>
#include <cmath>

namespace jej
{

    int Shape::m_ShapeIDCounter = 0;
    int Shape::m_RemovedShapeIDCounter = 0;

    Shape::~Shape()
    {
        ++m_RemovedShapeIDCounter;
    }
    ///////////////////////////////////////////


    std::vector<Vector2f> Shape::GetPoints() const
    {
        return m_points;
    }
    ///////////////////////////////////////////


    bool Shape::SetPoints(const std::vector<Vector2f>& p_newPoints)
    {
        if (m_points.size() == p_newPoints.size())
        {
            m_points = p_newPoints;
            return true;
        }

        return false;
    }
    ///////////////////////////////////////////


    unsigned int Shape::GetID() const
    {
        return m_ID;
    }
    ///////////////////////////////////////////


    void Shape::_addShape(const float p_radius, const unsigned int p_accuracy)
    {
        const unsigned int pointCount = p_accuracy > 3u ? p_accuracy : 3u;
        const float radians = (8.f * atan(1.f)) / pointCount;

        m_points.reserve(pointCount + 1u);
        float theta = 0.f;

        for (unsigned int i = 0u; i < pointCount; ++i)
        {
            m_points.emplace_back(
                ((cos(theta) * p_radius) / p_radius + 1.f) * 0.5f,
                1.f - ((sin(theta) * p_radius) / p_radius + 1.f) * 0.5f
                );

            theta += radians;
        }
        m_radius = p_radius;
        m_shapeType = ShapeType::Circle;

    }
    ///////////////////////////////////////////


    void Shape::_addShape(const Vector2f& p_extents)
    {
        m_points.reserve(4u);

        m_points.emplace_back(p_extents.x, p_extents.y);
        m_points.emplace_back(-p_extents.x, p_extents.y);
        m_points.emplace_back(-p_extents.x, -p_extents.y);
        m_points.emplace_back(p_extents.x, -p_extents.y);

        m_shapeType = ShapeType::Rectangle;
    }
    ///////////////////////////////////////////


    void Shape::_addShape(const std::vector<Vector2f>& p_points)
    {
        m_points.reserve(p_points.size());
        m_points = p_points;

        if (m_points.size() == 3u)
            m_shapeType = ShapeType::Triangle;
        else
            m_shapeType = ShapeType::Convex;
    }
    ///////////////////////////////////////////


    void Shape::_addShape()
    {
        m_points.reserve(3u);
        m_points.emplace_back(0.f, 1.f);
        m_points.emplace_back(-1.f, 0.f);
        m_points.emplace_back(1.f, 0.f);
        m_shapeType = ShapeType::Triangle;
    }
    ///////////////////////////////////////////


    float Shape::GetRadius() const
    {
        return m_radius;
    }
    ///////////////////////////////////////////


    const ShapeType Shape::GetType() const
    {
        return m_shapeType;
    }
    ///////////////////////////////////////////


}
