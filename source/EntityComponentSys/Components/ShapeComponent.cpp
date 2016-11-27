#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{

    ShapeComponent::ShapeComponent(Entity* p_entity, const Vector4i& p_color) :
        Component(p_entity),
        ColorRGBA(p_color),
		m_shapes{}
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

}