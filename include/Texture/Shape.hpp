#ifndef JEJ_SHAPE_HPP
#define JEJ_SHAPE_HPP

#include <Core/BaseStructs.hpp>

#include <vector>

#include <External/OpenGL_ES2/GLES2/gl2.h>

namespace jej
{
	

    class Shape
    {
        //ShapeComponent must have access to m_points
        friend class ShapeComponent;

        //Friend RenderComponent so it can get m_shapeType and texID
        friend class RenderSystem;

        //temo
        friend class TextureSystem;

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

        float GetRadius() const;

        const ShapeType GetType() const;

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

        std::vector<Vector2f> m_points;

        float m_radius;
        int m_textureID;
        
        unsigned int m_ID;
                
        static int m_ShapeIDCounter;
        static int m_RemovedShapeIDCounter;

    };

#include <Texture/Inl/Shape.inl>

}

#endif