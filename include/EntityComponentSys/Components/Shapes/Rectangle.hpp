#ifndef JEJ_RECTANGLE_HPP
#define JEJ_RECTANGLE_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{

    class Rectangle : public Shape
    {


    public:

        //Default constructor
        Rectangle();

        //Constructor
        Rectangle(const float x, const float y);

        //Destructor
        virtual ~Rectangle();

        //bool Transform(const std::vector<float>& p_newPoints) override;


    private:

        void _load(const float x, const float y);

    };

}

#endif