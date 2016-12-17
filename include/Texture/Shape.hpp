#ifndef JEJ_SHAPE_HPP
#define JEJ_SHAPE_HPP

#include <Core/BaseStructs.hpp>
#include <Core/Settings.hpp>

#include <vector>

#include <External/OpenGL_ES2/GLES2/gl2.h>

namespace jej
{
    namespace detail
    {
        struct DrawableData
        {
            std::vector<GLushort> indices;
            std::vector<GLfloat> vertices;
            std::vector<GLfloat> textureCoords;
            std::vector<GLint> colorValues;
            GLuint indicesBuffer;
            GLuint vertexPosBuffer;
            GLuint texCoordBuffer;
            GLuint colorValBuffer;

            GLuint vertexPositionIndex;
            GLuint textureCoordIndex;
            GLuint colorValuesIndex;

            ShapeType shapeType;
            bool hasChanged;

            GLuint shaderProgID;

            DrawableData() :
                indices(),
                vertices(),
                textureCoords(),
                colorValues(),
                indicesBuffer(0),
                vertexPosBuffer(0),
                texCoordBuffer(0),
                colorValBuffer(),
                vertexPositionIndex(0),
                textureCoordIndex(0),
                colorValuesIndex(),
                shapeType(ShapeType::Failed),
                hasChanged(false),
                shaderProgID(0)
            {
            }

        };
    }


    class Shape
    {
        //ShapeComponent must have access to m_points
        friend class ShapeComponent;

        //Friend RenderComponent so it can get m_shapeType and texID
        friend class RenderSystem;

        //temo
        friend class TextureSystem;

        friend class ShapeSystem;




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

        JEJ_COUNT GetID() const;

        float GetRadius() const;

        const ShapeType GetType() const;

    private:



        //Circle
        void _addShape(const float p_radius, const unsigned int p_accuracy, const Vector4i& p_myColor = Vector4i(0, 0, 0, 0));

        //Rectangle
        void _addShape(const Vector2f& p_extents, const Vector4i& p_myColor = Vector4i(0, 0, 0, 0));

        //Convex
        void _addShape(const std::vector<Vector2f>& p_points, const Vector4i& p_myColor = Vector4i(0, 0, 0, 0));

        //Empty args
        void _addShape(const Vector4i& p_myColor = Vector4i(0, 0, 0, 0));

        ShapeType m_shapeType;

        std::vector<Vector2f> m_points;

        float m_radius;
        int m_textureID;

        JEJ_COUNT m_ID;

        static JEJ_COUNT m_ShapeIDCounter;
        static JEJ_COUNT m_RemovedShapeIDCounter;

        Vector4i m_myColor;

        detail::DrawableData m_myDrawData;
    };

#include <Texture/Inl/Shape.inl>

}

#endif