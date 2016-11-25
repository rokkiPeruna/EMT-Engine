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
        bool SetPoints(const std::vector<Vector2f>& p_newPoints);

        unsigned int GetID() const;

    protected:

        ShapeType m_shapeType;
        
        std::vector<Vector2f> m_points;

        unsigned int m_ID;
        static int m_ShapeIDCounter;
        static int m_RemovedShapeIDCounter;

        virtual void _update(const float p_deltaTime) = 0;

    private:



    };


}

#endif