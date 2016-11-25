#include <EntityComponentSys/Components/ShapeComponent.hpp>
#include <EntityComponentSys/Components/Shapes/Circle.hpp>
#include <EntityComponentSys/Components/Shapes/Convex.hpp>
#include <EntityComponentSys/Components/Shapes/Rectangle.hpp>
#include <EntityComponentSys/Components/Shapes/Triangle.hpp>

namespace jej
{

    ShapeComponent::ShapeComponent(Entity& entity) :
        Component(entity),
        m_shapes()
    {
        m_componentType = ComponentType::Shape;
    }


    ShapeComponent::~ShapeComponent()
    {

    }

    bool ShapeComponent::RemoveShape(const unsigned int p_ID)
    {
        for (unsigned int i = 0; i < m_shapes.size(); ++i)
        
            if (m_shapes[i]->GetID() == p_ID)
            {
                m_shapes.erase(m_shapes.begin() + i);
                return true;
            }
        return false;
    }

    Circle* ShapeComponent::AddShape(const float radius, const unsigned int accuracy)
    {
        m_shapes.emplace_back(std::make_shared<Circle>(radius, accuracy));
        return dynamic_cast<Circle*>(m_shapes.back().get());
    }

    Convex* ShapeComponent::AddShape(const std::vector<float> points)
    {
        m_shapes.emplace_back(std::make_shared<Convex>(points));
        return dynamic_cast<Convex*>(m_shapes.back().get());
    }

    Rectangle* ShapeComponent::AddShape(const float x, const float y)
    {
        m_shapes.emplace_back(std::make_shared<Rectangle>(x, y));
        return dynamic_cast<Rectangle*>(m_shapes.back().get());
    }

    Triangle* ShapeComponent::AddShape(const float(&points)[6])
    {
        m_shapes.emplace_back(std::make_shared<Triangle>(points));
        return dynamic_cast<Triangle*>(m_shapes.back().get());
    }
}