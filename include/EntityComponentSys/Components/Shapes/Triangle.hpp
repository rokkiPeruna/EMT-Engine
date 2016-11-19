#ifndef JEJ_TRIANGLE_HPP
#define JEJ_TRIANGLE_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{

    class Triangle : ShapeComponent
    {
    private:
        Vector2f m_points[3];

    public:

        Triangle();

        //Constructor
        Triangle(const Vector2f p_points[3]);

        //Destructor
        virtual ~Triangle();
    };

}

#endif