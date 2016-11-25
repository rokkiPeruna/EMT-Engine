#ifndef JEJ_TRIANGLE_HPP
#define JEJ_TRIANGLE_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{

    class Triangle : public Shape
    {


    public:

        //Default constructor
        Triangle();

        //Constructor
        Triangle(const float(&p_points)[6]);

        //Destructor
        virtual ~Triangle();

    protected:

        void _update(const float p_deltaTime) override;

    private:

        void _load(const float(&p_points)[6]);

    };

}

#endif