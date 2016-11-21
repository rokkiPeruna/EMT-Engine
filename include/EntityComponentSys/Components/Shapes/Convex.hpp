#ifndef JEJ_CONVEX_HPP
#define JEJ_CONVEX_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{
    class Convex : public Shape
    {


    public:

        //Default constructor
        Convex();

        //Constructor
        Convex(const std::vector<float>& p_points);

        //Destructor
        virtual ~Convex();

        //bool Transform(const std::vector<float>& p_newPoints) override;

    private:

        void _load(const std::vector<float>& p_points);

    };


}

#endif