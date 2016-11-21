#ifndef JEJ_SHAPE_COMPONENT_HPP
#define JEJ_SHAPE_COMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>
#include <EntityComponentSys/Components/Shapes/Shape.hpp>

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

        

    public:

        //Constructor
        ShapeComponent(Entity& entity);

        //Destructor
        virtual ~ShapeComponent();

        //Add a shape to this component
        template <typename T, typename ... Args>
        T& AddShape(const ShapeType p_type, const Args& ... p_args);


    private:

        std::vector<std::shared_ptr<Shape>> m_shapes;
   
	};

#include <EntityComponentSys/Components/Inl/ShapeComponent.inl>

}

#endif