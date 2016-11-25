#ifndef JEJ_SHAPE_COMPONENT_HPP
#define JEJ_SHAPE_COMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>
#include <EntityComponentSys/Components/Shapes/Shape.hpp>


#include <memory>

namespace jej
{
    class Circle;
    class Convex;
    class Rectangle;
    class Triangle;

    class ShapeComponent : public Component
    {

        

    public:

        //Constructor
        ShapeComponent(Entity& entity);

        //Destructor
        virtual ~ShapeComponent();

        //Add a shape to this component
        template <typename T>
        T* AddShape();

        //Add a shape to this component
        Circle* AddShape(const float radius, const unsigned int accuracy);

        Convex* AddShape(const std::vector<float> points);

        Rectangle* AddShape(const float x, const float y);

        Triangle* AddShape(const float(&points)[6]);

        bool RemoveShape(const unsigned int p_ID);


    private:

        std::vector<std::shared_ptr<Shape>> m_shapes;

      
	};

#include <EntityComponentSys/Components/Inl/ShapeComponent.inl>

}

#endif