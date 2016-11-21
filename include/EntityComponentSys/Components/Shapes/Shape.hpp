#ifndef JEJ_SHAPE_HPP
#define JEJ_SHAPE_HPP

#include <Core/BaseStructs.hpp>

#include <vector>

namespace jej
{

    class Shape
    {

    public:

        //Constructor
        Shape();

        //Destructor
        ~Shape();

        //Return m_points
        std::vector<Vector2f> GetPoints() const;

        //Set new points
        //Point count (vector size) must match
        bool SetPoints(const std::vector<float>& p_newPoints);

    protected:

        ShapeType m_shapeType;
        
        std::vector<Vector2f> m_points;

    private:



    };


}

#endif