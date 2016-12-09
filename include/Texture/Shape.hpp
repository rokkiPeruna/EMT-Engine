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

			ShapeType m_shapeType = ShapeType::Failed;

			GLuint shaderProgID;

			DrawableData() :
				indicesBuffer(0),
				vertexPosBuffer(0),
				texCoordBuffer(0),
				vertexPositionIndex(0),
				textureCoordIndex(0),
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

		unsigned int GetID() const;

		float GetRadius() const;

		const ShapeType GetType() const;

	private:



		//Circle
		void _addShape(const float p_radius, const unsigned int p_accuracy, const Vector4i p_myColor = { 0, 0, 0, 0 });

		//Rectangle
		void _addShape(const Vector2f& p_extents, const Vector4i p_myColor = { 0, 0, 0, 0 });

		//Convex
		void _addShape(const std::vector<Vector2f>& p_points, const Vector4i p_myColor = { 0, 0, 0, 0 });

		//Empty args
		void _addShape(const Vector4i p_myColor = { 0, 0, 0, 0 });

		ShapeType m_shapeType;

		std::vector<Vector2f> m_points;

		float m_radius;
		int m_textureID;

		unsigned int m_ID;

		static int m_ShapeIDCounter;
		static int m_RemovedShapeIDCounter;

		Vector4i m_myColor;

		detail::DrawableData m_myDrawData;
	};

#include <Texture/Inl/Shape.inl>

}

#endif