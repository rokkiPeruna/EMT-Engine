#ifndef JEJ_CIRCLE_HPP
#define JEJ_CIRCLE_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{
    class Circle : ShapeComponent
    {
    private:
        float m_radius;

    public:

        //Default constructor
        Circle(Entity& entity);

        //Constructor
        Circle(Entity& entity, const float radius);

        //Destructor
        virtual ~Circle();
    };


}

#endif