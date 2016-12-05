#ifndef JEJ_SHAPE_HPP
#define JEJ_SHAPE_HPP

#include <Core/BaseStructs.hpp>

#include <vector>

namespace jej
{

    class Shape
    {
		friend class Math;

        //ShapeComponent must have access to m_points
        friend class ShapeComponent;

        //Friend RenderComponent so it can get m_shapeType
        friend class RenderComponent;

    public:

        //Constructor with args
        template <typename ... Args>
        Shape(const Args& ... p_args);

        //Disabled copy-constructor
        NOCOPY(Shape);

        //Destructor
        ~Shape();

        //Return m_points
        std::vector<Vector2f> GetPoints() const;

        //Set new points
        //Point count (vector size) must match
        bool SetPoints(const std::vector<Vector2f>& p_newPoints);

        unsigned int GetID() const;

		const float GetRadius() const;

    private:

        

        //Circle
        void _addShape(const float p_radius, const unsigned int p_accuracy);

        //Rectangle
        void _addShape(const Vector2f& p_extents);

        //Convex
        void _addShape(const std::vector<Vector2f>& p_points);

        //Empty args
        void _addShape();

        ShapeType m_shapeType;
		float m_radius;
        std::vector<Vector2f> m_points;

        unsigned int m_ID;
        static int m_ShapeIDCounter;
        static int m_RemovedShapeIDCounter;

    };

#include <Texture/Inl/Shape.inl>

}

#endif