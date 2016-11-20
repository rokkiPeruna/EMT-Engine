#ifndef JEJ_SHAPE_COMPONENT_HPP
#define JEJ_SHAPE_COMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>
#include <Core/BaseStructs.hpp>

namespace jej
{

    class ShapeComponent : public Component
    {

    public:
        //Constructor
        ShapeComponent(Entity& entity);

        //Destructor
        virtual ~ShapeComponent();



    protected:

        ShapeType m_shapeType;

    };

}

#endif