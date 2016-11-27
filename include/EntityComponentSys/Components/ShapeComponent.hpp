#ifndef JEJ_SHAPE_COMPONENT_HPP
#define JEJ_SHAPE_COMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>
#include <EntityComponentSys/Components/Shapes/Shape.hpp>
#include <Core/BaseStructs.hpp>

//#include <EntityComponentSys/Components/Shapes/Circle.hpp>
//#include <EntityComponentSys/Components/Shapes/Convex.hpp>
//#include <EntityComponentSys/Components/Shapes/Rectangle.hpp>
//#include <EntityComponentSys/Components/Shapes/Triangle.hpp>

#include <memory>

namespace jej
{
    class Circle;

    class ShapeComponent : public Component
    {
        friend class RenderSystem;
        friend class RenderComponent;

    public:

        //Constructor
        ShapeComponent(Entity& entity, Vector4i p_color = { 255, 0, 0, 255 });

        //Destructor
        virtual ~ShapeComponent();

        //Add a shape to this component
        template <typename T,  typename ... Args>
        void AddShape(const T, Args& ... p_args);

        //Shapes' color
        Vector4i ColorRGBA;

    private:

        std::vector<std::shared_ptr<Shape>> m_shapes;

    };

#include <EntityComponentSys/Components/Inl/ShapeComponent.inl>

}

#endif