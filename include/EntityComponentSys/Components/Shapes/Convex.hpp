#ifndef JEJ_CONVEX_HPP
#define JEJ_CONVEX_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{
    class Convex : ShapeComponent
    {
    private:
        unsigned int m_pointCount;
        Vector2f *m_points;

    public:

        //Default constructor
        Convex(Entity& entity);

        //Constructor
        Convex(Entity& entity, const unsigned int p_pointCount, Vector2f*p_points);

        //Destructor
        virtual ~Convex();
    };


}

#endif